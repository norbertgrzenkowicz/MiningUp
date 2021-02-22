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
	
	//Inicjalizacja pocz¹tkowego stanu gry, Menu
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
				UI->menu->moving(*window, event);	//poruszanie siê w menu
			}

			window->clear();
			tlo->drawBackground(*window);			//rysowanie t³a
			UI->menu->drawMenu(*window);			//rysowanie menu

			window->display();
			break;

		case STATE_CHOOSINGDIFFICULTY:	//Stan wybierania poziomu trudnoœci
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();

				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape) //cofniêcie siê do Menu
					{
						UI->menu->choose_difficulty = false;
						UI->menu->menu_start = true;
					}
				}
			}
			window->clear();
			tlo->drawBackground(*window);			//rysowanie t³a
			UI->chooseDifficulty(event, *window);	//Rysowanie oraz funkcjonowanie wyboru poziomu trudnoœci

			window->display();
			break;
		
		case STATE_PLAYERSCHART:	//Stan wyników graczy
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window->close();
				
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape) //cofniêcie siê do Menu
					{
						UI->menu->playersChart = false;
						UI->menu->menu_start = true;
					}
				}
			}
			window->clear();	
			tlo->drawBackground(*window);			//rysowanie t³a
			UI->playersScore(event, *window);		//Rysowanie wyników

			window->display();
			break;


		case STATE_GAME:	//Stan gry

			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					if (gracz->getLavaTouched() != true) //Przy wy³¹czeniu okna nastêpuje zapis gry
						UI->save(event, gracz->getPosition(), mapa->get_typ_kafli(), lawa->getLavaSurfacePos(), mapa->getGatheredDiamonds(), mapa->getGatheredIron());
					window->close();
				}
				if (event.type == sf::Event::KeyPressed) //Zapytanie czy chce siê wyjœæ z gry
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						UI->set_escape(true);
					}
				}
			}

			window->clear();
			//mapatimingChange(dt);

			tlo->drawGameBackground(*window); //Rysowanie t³a gry

			gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched()); //Kamera pod¹¿aj¹ca za graczem


			if (UI->menu->set_newGame == true) //Nowa gra
			{
				//Ustawianie mno¿ników trudnoœci oraz tekstury
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

			if (UI->get_renew() == true) //Powtórzenie gry
			{
				//Ustawianie mno¿ników trudnoœci oraz tekstury
				mapa->setDifficultyMultiplier(UI->get_difficulty());
				lawa->setDifficultyMultiplier(UI->get_difficulty());
				gracz->setPickaxe(UI->get_difficulty());
				
				//generowanie gry
				mapa->generateTiles();
				mapa->map();
				window->setView(window->getDefaultView());
				gracz->setPositionDefault();
				lawa->setPositionDefault();
				gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched()); //przywrócenie kamery pod¹¿aj¹cej za graczem
				mapa->setDiamondsDefault();
				UI->set_renew(false);
				UI->Pause = false;
			}

			if (gracz->getLavaTouched() != true) //Póki gracz jest ¿ywy
			{
				if (UI->Pause != true) //Póki gra nie jest zapauzowana
				{
					mapa->positioning(*window, gracz->getPosition(), gracz->getBounds());	//Pozycjonowanie myszki
					gracz->objectCollisionToTileMap(mapa);									//Kolizja obiektów
					mapa->destroyTile(dt, event);											//Niszczenie bloków
					
					//Dynamiczne generowanie siê pierwszych bloków wraz z niszczeniem ostatnich wzglêdem pozycji graczy
					window->setView(window->getDefaultView());
					gracz->setPosition(mapa->tilesDown(gracz->getPosition()));
					lawa->isTileDown(mapa->get_isTileDown());			
					lawa->moveUp(dt); //ruch lawy
					gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched()); //przywrócenie kamery pod¹¿aj¹cej za graczem

					//Ruch gracza
					gracz->move(dt, event); 
					gracz->didLavaTouched(lawa->getLavaSurfacePos()); //Jeœli gracz dotknie lawy, gra zostaje zakoñczona.

					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::F4) // zapis gry podczas klikniêcia przycisku F4
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
			//window->draw(mapa->getText()); //Odkomentowaæ dla uruchomienia dodatkowego interfejsu pozycji myszki

			if (gracz->getLavaTouched() != true)
				UI->inGameUI(event, *window, mapa->getGatheredDiamonds(), mapa->getGatheredIron()); //Interfejs gracza podczas gry
			if (gracz->getLavaTouched() == true) //Œmieræ = intersekcja gracza z law¹
			{
				UI->saveDead(mapa->getGatheredDiamonds(), mapa->getGatheredIron(), UI->get_difficulty()); //zapis statystyk
				this->loadMenuAfterDeath(UI->endGameMenu(gracz->death(dt, gracz->getLavaTouched()), event, *window)); //Menu poœmiertne
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
	if (UI->menu->loadGame == true)				//Wybór wczytania zapisanej gry
	{
		UI->loadGame();
		this->loadSavedGame();
		UI->menu->loadGame = false;
		UI->menu->game_start = true;
	}
	if (UI->menu->choose_difficulty == true)	//stan wybierania poziomu trudnoœci
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

void Game::loadMenuAfterDeath(bool back) //ustawienie zmiennych potrzebnych do za³adowania menu poœmiertnego
{
	if (back == true)
	{
		UI->menu->menu_start = true;
		UI->menu->choose_difficulty = false;
		UI->menu->game_start = false;
	}
}