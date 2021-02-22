#include "Buttons.h"

#define MAX_ITEMS 4 //zdefiniowanie maksymalnej warto�ci element�w w menu g��wnym

class Menu
{
private:
	int selectedMenuitem; //wybrany element w menu g��wnym
	
	//elementy tekstu
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

	sf::Text* tytul;

public:
	Menu();
	Menu(float width, float height);
	~Menu();

	void moving(sf::RenderWindow& window, sf::Event& event);	//Poruszanie si� w menu g��wnym
	void drawMenu(sf::RenderWindow& window);					//Rysowanie menu
	void MoveUp();												//Ruch w g�r�
	void MoveDown();											//Ruch w d�

	int get_SelectedItem() { return selectedMenuitem; };			//Zwraca wybrany element w Menu g��wnym

	//Pomocnicze stanu gry
	bool menu_start;			//start menu
	bool game_start;			//start gry
	bool set_newGame;			//wyb�r nowej gry
	bool loadGame;				//wyb�r za�adowania gry
	bool choose_difficulty;		//wyb�r poziomu trudno�ci
	bool playersChart;			//wyb�r menu statystyk graczy
};