#pragma once
#include "Background.h"

class Game
{
private:
	sf::RenderWindow *window;
	sf::Clock dtClock;
	float dt;
	//typ wyliczeniowy potrzebny do zmieniania stanu gry mi�dzy menu, wybieraniem trudnos�i, wynik�w graczy oraz gry
	enum State
	{
		STATE_MENU,					//menu
		STATE_CHOOSINGDIFFICULTY,	//wybieranie poziomu trudno�ci gry
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
	Background* tlo;	//Wczytywanie t�a

	
public:
	Game();
	~Game();

	void run();							//Metoda zawiera g��wn� p�tle gry wraz z jej wszystkimi elementami
	void checkGameState();				//Sprawdza oraz zmienia stany gry
	void loadSavedGame();				//�aduje gr�
	void loadMenuAfterDeath(bool back);	//�aduje menu po przegraniu gry
};