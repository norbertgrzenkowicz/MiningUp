#include "Buttons.h"

#define MAX_ITEMS 4 //zdefiniowanie maksymalnej wartoœci elementów w menu g³ównym

class Menu
{
private:
	int selectedMenuitem; //wybrany element w menu g³ównym
	
	//elementy tekstu
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

	sf::Text* tytul;

public:
	Menu();
	Menu(float width, float height);
	~Menu();

	void moving(sf::RenderWindow& window, sf::Event& event);	//Poruszanie siê w menu g³ównym
	void drawMenu(sf::RenderWindow& window);					//Rysowanie menu
	void MoveUp();												//Ruch w górê
	void MoveDown();											//Ruch w dó³

	int get_SelectedItem() { return selectedMenuitem; };			//Zwraca wybrany element w Menu g³ównym

	//Pomocnicze stanu gry
	bool menu_start;			//start menu
	bool game_start;			//start gry
	bool set_newGame;			//wybór nowej gry
	bool loadGame;				//wybór za³adowania gry
	bool choose_difficulty;		//wybór poziomu trudnoœci
	bool playersChart;			//wybór menu statystyk graczy
};