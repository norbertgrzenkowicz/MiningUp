#include "Game.h"



Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "The Dungeon");	//Inicjalizacja okna
	window->setFramerateLimit(165);													//Ustawienie limitu klatek gry

	//Inicjalizacja klas
	UI = new UserInterface(*window);
	gracz = new player;
	lawa = new Lava;
	mapa = new TileMap;
	gameCamera = new Camera(window->getSize());
	tlo = new Background(window->getSize());
	
	//Inicjalizacja pocz�tkowego stanu gry, Menu
	state_ = STATE_MENU;

	//Czas rzeczywisty
	dt = 0;
}

Game::~Game()
{
	delete UI, gameCamera, gracz, mapa, lawa, tlo, window;
}

void Game::run()
{
	while (window->isOpen())
	{
		sf::Event event;
		dt = dtClock.restart().asSeconds();

		this->checkGameState();

		switch (state_)
		{
		case STATE_MENU:		//Stan menu
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();
				UI->menu->moving(*window, event);	//poruszanie si� w menu
			}

			window->clear();
			tlo->drawBackground(*window);			//rysowanie t�a
			UI->menu->drawMenu(*window);			//rysowanie menu

			window->display();
			break;

		case STATE_CHOOSINGDIFFICULTY:	//Stan wybierania poziomu trudno�ci
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();

				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape) //cofni�cie si� do Menu
					{
						UI->menu->choose_difficulty = false;
						UI->menu->menu_start = true;
					}
				}
			}
			window->clear();
			tlo->drawBackground(*window);			//rysowanie t�a
			UI->chooseDifficulty(event, *window);	//Rysowanie oraz funkcjonowanie wyboru poziomu trudno�ci

			window->display();
			break;
		
		case STATE_PLAYERSCHART:	//Stan wynik�w graczy
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();
				
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape) //cofni�cie si� do Menu
					{
						UI->menu->playersChart = false;
						UI->menu->menu_start = true;
					}
				}
			}
			window->clear();	
			tlo->drawBackground(*window);			//rysowanie t�a
			UI->playersScore(event, *window);		//Rysowanie wynik�w

			window->display();
			break;


		case STATE_GAME:	//Stan gry

			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					if (gracz->getLavaTouched() != true) //Przy wy��czeniu okna nast�puje zapis gry
						UI->save(event, gracz->getPosition(), mapa->get_typ_kafli(), lawa->getLavaSurfacePos(), mapa->getGatheredDiamonds(), mapa->getGatheredIron());
					window->close();
				}
				if (event.type == sf::Event::KeyPressed) //Zapytanie czy chce si� wyj�� z gry
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						UI->set_escape(true);
					}
				}
			}

			window->clear();
			//mapatimingChange(dt);

			tlo->drawGameBackground(*window); //Rysowanie t�a gry

			gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched()); //Kamera pod��aj�ca za graczem


			if (UI->menu->set_newGame == true) //Nowa gra
			{
				//Ustawianie mno�nik�w trudno�ci oraz tekstury
				mapa->setDifficultyMultiplier(UI->get_difficulty());
				lawa->setDifficultyMultiplier(UI->get_difficulty());
				gracz->setPickaxe(UI->get_difficulty());

				//generowanie gry
				mapa->generateTiles();
				mapa->map();
				gracz->setPositionDefault();
				lawa->setPositionDefault();
				mapa->setDiamondsDefault();
				UI->Pause = false;
				UI->menu->set_newGame = false;
			}

			if (UI->get_renew() == true) //Powt�rzenie gry
			{
				//Ustawianie mno�nik�w trudno�ci oraz tekstury
				mapa->setDifficultyMultiplier(UI->get_difficulty());
				lawa->setDifficultyMultiplier(UI->get_difficulty());
				gracz->setPickaxe(UI->get_difficulty());
				
				//generowanie gry
				mapa->generateTiles();
				mapa->map();
				window->setView(window->getDefaultView());
				gracz->setPositionDefault();
				lawa->setPositionDefault();
				gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched()); //przywr�cenie kamery pod��aj�cej za graczem
				mapa->setDiamondsDefault();
				UI->set_renew(false);
				UI->Pause = false;
			}

			if (gracz->getLavaTouched() != true) //P�ki gracz jest �ywy
			{
				if (UI->Pause != true) //P�ki gra nie jest zapauzowana
				{
					mapa->positioning(*window, gracz->getPosition(), gracz->getBounds());	//Pozycjonowanie myszki
					gracz->objectCollisionToTileMap(mapa);									//Kolizja obiekt�w
					mapa->destroyTile(dt, event);											//Niszczenie blok�w
					
					//Dynamiczne generowanie si� pierwszych blok�w wraz z niszczeniem ostatnich wzgl�dem pozycji graczy
					window->setView(window->getDefaultView());
					gracz->setPosition(mapa->tilesDown(gracz->getPosition()));
					lawa->isTileDown(mapa->get_isTileDown());			
					lawa->moveUp(dt); //ruch lawy
					gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched()); //przywr�cenie kamery pod��aj�cej za graczem

					//Ruch gracza
					gracz->move(dt, event); 
					gracz->didLavaTouched(lawa->getLavaSurfacePos()); //Je�li gracz dotknie lawy, gra zostaje zako�czona.

					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::F4) // zapis gry podczas klikni�cia przycisku F4
							UI->save(event, gracz->getPosition(), mapa->get_typ_kafli(), lawa->getLavaSurfacePos(), mapa->getGatheredDiamonds(), mapa->getGatheredIron());
					}
				}
			}


			//rysowanie elementow gry

			mapa->draw(*window);
			mapa->drawDestroyAnimation(*window);
			lawa->draw(*window);
			gracz->draw(window);

			//reset kamery
			window->setView(window->getDefaultView());

			//UI
			//window->draw(mapa->getText()); //Odkomentowa� dla uruchomienia dodatkowego interfejsu pozycji myszki

			if (gracz->getLavaTouched() != true)
				UI->inGameUI(event, *window, mapa->getGatheredDiamonds(), mapa->getGatheredIron()); //Interfejs gracza podczas gry
			if (gracz->getLavaTouched() == true) //�mier� = intersekcja gracza z law�
			{
				UI->saveDead(mapa->getGatheredDiamonds(), mapa->getGatheredIron(), UI->get_difficulty()); //zapis statystyk
				this->loadMenuAfterDeath(UI->endGameMenu(gracz->death(dt, gracz->getLavaTouched()), event, *window)); //Menu po�miertne
			}
			window->display();
			break;
		}
	}
}

void Game::checkGameState()
{
	if (UI->menu->menu_start == true)			//stan menu
	{
		state_ = STATE_MENU;
	}
	if (UI->menu->loadGame == true)				//Wyb�r wczytania zapisanej gry
	{
		UI->loadGame();
		this->loadSavedGame();
		UI->menu->loadGame = false;
		UI->menu->game_start = true;
	}
	if (UI->menu->choose_difficulty == true)	//stan wybierania poziomu trudno�ci
	{
		state_ = STATE_CHOOSINGDIFFICULTY;
	}
	if (UI->menu->playersChart == true)			//stan statystyk graczy
	{
		state_ = STATE_PLAYERSCHART;
	}
	if (UI->menu->game_start == true)			//stan gry
	{
		state_ = STATE_GAME;
	}
}

void Game::loadSavedGame() //wczytywanie gry
{

	UI->set_difficulty(UI->get_loadedDifficulty());
	mapa->setDifficultyMultiplier(UI->get_loadedDifficulty());
	lawa->setDifficultyMultiplier(UI->get_loadedDifficulty());
	gracz->setPickaxe(UI->get_loadedDifficulty());
	mapa->set_typ_kafli(UI->get_loadedTypy_kafli());
	mapa->map();
	gracz->setPosition(UI->get_loadedGamerPos());
	lawa->setPosition(UI->get_loadedLavaPos());		
	mapa->setDiamonds(UI->get_loadeddiamonds());
	mapa->setIron(UI->get_loadediron());
}

void Game::loadMenuAfterDeath(bool back) //ustawienie zmiennych potrzebnych do za�adowania menu po�miertnego
{
	if (back == true)
	{
		UI->menu->menu_start = true;
		UI->menu->choose_difficulty = false;
		UI->menu->game_start = false;
	}
}