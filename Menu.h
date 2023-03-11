#include "Buttons.h"
#include "Entity.h"

#define MAX_ITEMS 4 //zdefiniowanie maksymalnej wartoci elementw w menu gwnym

#define set_text(textOb, color, text, size, positionX, positionY) \
	textOb.setFont(font);				\
	textOb.setFillColor(sf::Color::White);\
	textOb.setString(text);\
	textOb.setCharacterSize(size); \
	textOb.setPosition(positionX, positionY);

#define set_number(number, color, size) \
	number.setFont(font);					\
	number.setFillColor(sf::Color::White);	\
	number.setCharacterSize(size);


class Menu : public Entity_iface
{
private:
	int selectedMenuitem; //wybrany element w menu gwnym
	
	//elementy tekstu
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

	sf::Text tytul;

	//Pomocnicze stanu gry
	bool menu_start;			//start menu
	bool game_start;			//start gry
	bool newGame;			//wybr nowej gry
	bool loadGame;				//wybr zaadowania gry
	bool choose_difficulty;		//wybr poziomu trudnoci
	bool playersChart;			//wybr menu statystyk graczy

public:
	Menu();
	Menu(float width, float height);
	~Menu();

	void moving(sf::RenderWindow& window, sf::Event& event);	//Poruszanie si w menu gwnym
	void draw(sf::RenderWindow& window) final;					//Rysowanie menu
	void MoveUp();												//Ruch w gr
	void MoveDown();											//Ruch w d

	int get_SelectedItem() { return selectedMenuitem; };			//Zwraca wybrany element w Menu gwnym

	void set_menu_start(bool menu_start);
	void set_game_start(bool game_start);
	void set_newGame(bool newGame);
	void set_loadGame(bool loadGame);
	void set_choose_difficulty(bool choose_difficulty);
	void set_playersChart(bool playersChart);

	bool get_menu_start();
	bool get_game_start();
	bool get_newGame();
	bool get_loadGame();
	bool get_choose_difficulty();
	bool get_playersChart();
};
