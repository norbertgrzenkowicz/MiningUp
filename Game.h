#pragma once
#include "Background.h"

class Game
{
private:
	sf::RenderWindow *window;
	sf::Clock dtClock;
	float dt;
	//typ wyliczeniowy potrzebny do zmieniania stanu gry miêdzy menu, wybieraniem trudnosæi, wyników graczy oraz gry
	enum State
	{
		STATE_MENU,					//menu
		STATE_CHOOSINGDIFFICULTY,	//wybieranie poziomu trudnoœci gry
		STATE_PLAYERSCHART,			//Wyniki graczy
		STATE_GAME					//gra
	};
	enum State state_;

	//Inicjalizacja klas
	UserInterface* UI;	//Interfejs gracza
	Camera* gameCamera;	//Kamera
	player* gracz;		//Jednostka sterowalna
	TileMap* mapa;		//Otoczenie gracza
	Lava* lawa;			
	Background* tlo;	//Wczytywanie t³a

	
public:
	Game();
	~Game();

	void run();							//Metoda zawiera g³ówn¹ pêtle gry wraz z jej wszystkimi elementami
	void checkGameState();				//Sprawdza oraz zmienia stany gry
	void loadSavedGame();				//£aduje grê
	void loadMenuAfterDeath(bool back);	//£aduje menu po przegraniu gry
};