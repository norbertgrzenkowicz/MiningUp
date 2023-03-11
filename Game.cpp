#include "Game.h"

// #include <chrono>
// using namespace std::chrono;


Game::Game() :
	window(sf::VideoMode(1920, 1080), "The Dungeon")	//Inicjalizacja okna
{
	window.setFramerateLimit(165);													//Ustawienie limitu klatek gry

	//Inicjalizacja klas
	UI = std::make_unique<UserInterface>(window);
	gracz = std::make_unique<player>();
	lawa = std::make_unique<Lava>();
	mapa = std::make_unique<TileMap>();
	gameCamera = std::make_unique<Camera>(window.getSize());
	tlo = std::make_unique<Background>(window.getSize());
	
	//Inicjalizacja poczatkowego stanu gry, Menu
	state_ = STATE_MENU;

	//Czas rzeczywisty
	dt = 0;
}

Game::~Game()
{
}

void Game::run()
{
	while (window.isOpen())
	{
		// auto start = high_resolution_clock::now(); 6-8 at menu, 10-18 ingame
		sf::Event event;
		dt = dtClock.restart().asSeconds();

		this->checkGameState();

		switch (state_)
		{
		case STATE_MENU:		//Stan menu
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				UI->menu->moving(window, event);	//poruszanie sie w menu
			}

			window.clear();
			tlo->drawBackground(window);			//rysowanie tla
			UI->menu->draw(window);			//rysowanie menu

			window.display();
			break;

		case STATE_CHOOSINGDIFFICULTY:	//Stan wybierania poziomu trudnosci
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape) //cofniecie sie do Menu
					{
						UI->menu->set_choose_difficulty(false);
						UI->menu->set_menu_start(true);
					}
				}
			}
			window.clear();
			tlo->drawBackground(window);			//rysowanie tla
			UI->chooseDifficulty(event, window);	//Rysowanie oraz funkcjonowanie wyboru poziomu trudnoci

			window.display();
			break;
		
		case STATE_PLAYERSCHART:	//Stan wynikow graczy
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) //cofniecie sie do Menu
				{
					UI->menu->set_playersChart(false);
					UI->menu->set_menu_start(true);
				}
			}
			window.clear();	
			tlo->drawBackground(window);			//rysowanie tla
			UI->playersScore(event, window);		//Rysowanie wynikow

			window.display();
			break;


		case STATE_GAME:	//Stan gry

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					if (gracz->getLavaTouched() != true) //Przy wylaczeniu okna nastepuje zapis gry
						UI->save(event, gracz->getPosition(), mapa->get_typ_kafli(), lawa->getLavaSurfacePos(), mapa->getGatheredDiamonds(), mapa->getGatheredIron());
					window.close();
				}
				if (event.type == sf::Event::KeyPressed) //Zapytanie czy wyjsc z gry
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						UI->set_escape(true);
					}
				}
			}

			window.clear();
			//mapatimingChange(dt);

			tlo->draw(window);

			//odpalenie kamery
			gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched());

			if (UI->menu->get_newGame()) //Nowa gra
			{
				//Ustawianie mnoznikow trudnosci oraz tekstury
				mapa->setDifficultyMultiplier(UI->get_difficulty());
				lawa->setDifficultyMultiplier(UI->get_difficulty());
				gracz->setPickaxe(UI->get_difficulty());

				//generowanie gry
				mapa->generateTiles();
				mapa->map();
				gracz->setPositionDefault();
				lawa->setPositionDefault();
				mapa->setDiamondsDefault();
				UI->set_Pause(false);
				UI->menu->set_newGame(false);
			}

			if (UI->get_renew()) //Powtorzenie gry
			{
				//Ustawianie mnoznikow trudnosci oraz tekstury
				mapa->setDifficultyMultiplier(UI->get_difficulty());
				lawa->setDifficultyMultiplier(UI->get_difficulty());
				gracz->setPickaxe(UI->get_difficulty());
				
				//generowanie gry
				mapa->generateTiles();
				mapa->map();
				window.setView(window.getDefaultView());
				gracz->setPositionDefault();
				lawa->setPositionDefault();
				gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched()); //przywrocenie kamery podazajacej za graczem
				mapa->setDiamondsDefault();
				UI->set_renew(false);
				UI->set_Pause(false);
			}

			if (!gracz->getLavaTouched()) //Poki gracz jest zywy
			{
				if (!UI->get_Pause()) //Poki gra nie jest zapauzowana
				{
					mapa->positioning(window, gracz->getPosition(), gracz->getBounds());	//Pozycjonowanie myszki
					gracz->objectCollisionToTileMap(mapa.get());									//Kolizja obiektow
					mapa->destroyTile(dt, event);											//Niszczenie blokow
					
					//Dynamiczne generowanie sie pierwszych blokow wraz z niszczeniem ostatnich wzgledem pozycji graczy
					window.setView(window.getDefaultView());
					gracz->setPosition(mapa->tilesDown(gracz->getPosition()));
					lawa->isTileDown(mapa->get_isTileDown());			
					lawa->moveUp(dt); //ruch lawy
					gameCamera->followplayer(window, gracz->getPosition(), gracz->getBounds(), gracz->getLavaTouched()); //przywrocenie kamery podazaajacej za graczem

					//Ruch gracza
					gracz->move(dt, event); 
					gracz->didLavaTouched(lawa->getLavaSurfacePos()); //Jesli gracz dotknie lawy, gra zostaje zakoczona.

					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::F4) // zapis gry podczas klikniecia przycisku F4
							UI->save(event, gracz->getPosition(), mapa->get_typ_kafli(), lawa->getLavaSurfacePos(), mapa->getGatheredDiamonds(), mapa->getGatheredIron());
					}
				}
			}

			//rysowanie elementow gry

			mapa->draw(window);
			mapa->drawDestroyAnimation(window);
			lawa->draw(window);
			gracz->draw(window);

			//reset kamery
			window.setView(window.getDefaultView());

			//UI
			//window.draw(mapa->getText()); //Odkomentowac dla uruchomienia dodatkowego interfejsu pozycji myszki

			if (!gracz->getLavaTouched())
				UI->inGameUI(event, window, mapa->getGatheredDiamonds(), mapa->getGatheredIron()); //Interfejs gracza podczas gry
			if (gracz->getLavaTouched()) //smierc = intersekcja gracza z lawa
			{
				UI->saveDead(mapa->getGatheredDiamonds(), mapa->getGatheredIron(), UI->get_difficulty()); //zapis statystyk
				this->loadMenuAfterDeath(UI->endGameMenu(gracz->death(dt, gracz->getLavaTouched()), event, window)); //Menu posmiertne
			}
			window.display();
			break;
		}
		// auto stop = high_resolution_clock::now();
		// auto duration = duration_cast<milliseconds>(stop - start);
		// std::cout << duration.count() << std::endl;
	}
}

void Game::checkGameState()
{
	if (UI->menu->get_menu_start())			//stan menu
	{
		state_ = STATE_MENU;
	}
	if (UI->menu->get_loadGame())				//Wybor wczytania zapisanej gry
	{
		UI->loadGame();
		this->loadSavedGame();
		UI->menu->set_loadGame(false);
		UI->menu->set_game_start(true);
	}
	if (UI->menu->get_choose_difficulty())	//stan wybierania poziomu trudnosci
	{
		state_ = STATE_CHOOSINGDIFFICULTY;
	}
	if (UI->menu->get_playersChart())			//stan statystyk graczy
	{
		state_ = STATE_PLAYERSCHART;
	}
	if (UI->menu->get_game_start())			//stan gry
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

void Game::loadMenuAfterDeath(bool back) //ustawienie zmiennych potrzebnych do zaladowania menu posmiertnego
{
	if (back)
	{
		UI->menu->set_menu_start(true);
		UI->menu->set_choose_difficulty(false);
		UI->menu->set_game_start(false);
	}
}
