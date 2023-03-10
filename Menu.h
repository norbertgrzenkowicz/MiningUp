#include "Buttons.h"
#include "Entity.h"

#define MAX_ITEMS 4 //zdefiniowanie maksymalnej wartoci elementw w menu gwnym

class Menu : public Entity_iface
{
private:
	int selectedMenuitem; //wybrany element w menu gwnym
	
	//elementy tekstu
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

	sf::Text* tytul;

public:
	Menu();
	Menu(float width, float height);
	~Menu();

	void moving(sf::RenderWindow& window, sf::Event& event);	//Poruszanie si w menu gwnym
	void draw(sf::RenderWindow& window) final;					//Rysowanie menu
	void MoveUp();												//Ruch w gr
	void MoveDown();											//Ruch w d

	int get_SelectedItem() { return selectedMenuitem; };			//Zwraca wybrany element w Menu gwnym

	//Pomocnicze stanu gry
	bool menu_start;			//start menu
	bool game_start;			//start gry
	bool set_newGame;			//wybr nowej gry
	bool loadGame;				//wybr zaadowania gry
	bool choose_difficulty;		//wybr poziomu trudnoci
	bool playersChart;			//wybr menu statystyk graczy
};