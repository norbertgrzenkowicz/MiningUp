#include "Menu.h"


class UserInterface
	: public Buttons
{
private:

	//Zmienne pomocnicze stanw gry
	bool renew;
	bool helpMenuBool;
	bool isSaved;
	bool isLoaded;
	bool escape;

	unsigned int difficulty;

	//Przyciski
	Buttons* endGameBackToMenu;
	Buttons* easyButton;
	Buttons* mediumButton;
	Buttons* hardButton;
	Buttons* noButton;
	Buttons* yesButton;

	//Tekstura licznikw surowcw
	sf::Texture countUIT;
	sf::Sprite countUI;

	//Kontener przyciskw dla menu pauzy

	//Tekst
	sf::Font font;

	sf::Text* diamonds;
	sf::Text* iron;
	sf::Text* difficultyText;
	sf::Text* naglowek;
	sf::Text* kategorie;
	sf::Text* playerNumber;
	sf::Text* helpText;
	sf::Text* escBack;
	sf::Text* leave;
	sf::Text* gameOver;

	//Zmienne zaadowane
	sf::Vector2f loadedGamerPos;
	std::vector<std::vector<int>> loadedTypy_kafli;
	sf::Vector2f loadedLavaPos;
	unsigned int loadedDiamonds;
	unsigned int loadedIron;
	unsigned int loadedDifficulty;

	
	struct danegracza { //struktura graczy
		unsigned int diamondsCounted;
		unsigned int ironCounted;
		unsigned int difficulty;
	};
						//kontener graczy
	std::vector<danegracza> gracze;
public:

	Menu* menu;
	UserInterface(sf::RenderWindow& window);
	~UserInterface();


	void inGameUI(sf::Event& event, sf::RenderWindow& window, unsigned int diamondsCounted, unsigned int ironCounted);		//Interfejs gracza podczas gry
	void helpMenu(sf::Event& event, sf::RenderWindow& window);																//help Menu
	bool endGameMenu(bool isDead, sf::Event& event, sf::RenderWindow& window);												//Menu pomiertne
	void playersScore(sf::Event& event, sf::RenderWindow& window);															//Menu statystyk graczy
	void chooseDifficulty(sf::Event& event, sf::RenderWindow& window);														//Menu wyboru poziomu trudnoci

	void save(sf::Event event, sf::Vector2f playerPos, std::vector<std::vector<int>> tilemap, sf::Vector2f lavaPos, unsigned int diamondsCount, unsigned int ironCount); //Zapis gry
	void savePlayers(unsigned int diamondsCount, unsigned int ironCount, unsigned int difficulty);							//Zapis statystyk graczy
	void saveDead(unsigned int diamondsCount, unsigned int ironCount, unsigned int difficulty);								//Zapis statystyk po mierci
	void loadGame();																										//Odczyt gry
	void loadPlayers();																										//Odczyt graczy

	void putShadow(sf::RenderWindow& window);																				//Zaciemienie gry na czas pauzy/helpMenu
	void leaveQuestion(sf::Event& event, sf::RenderWindow& window);															//Zapytanie czy chcesz wyjsc z gry

	void set_escape(bool esc);																								//Ustawianie booleanu zapytania wyjcia z gry
	void set_renew(bool renewG);																							//Ustawianie booleanu odnowienia gry
	bool get_renew();																										//Odczyt booleanu odnowienia gry
	void set_difficulty(unsigned int difficulty);																			//Ustawianie poziomu trudnoci gry
	unsigned int get_difficulty();																							//Odczyt poziomu trudnoci gry

	std::vector<std::vector<int>> get_loadedTypy_kafli();																	//Odczyt typy_kafli z pliku
	sf::Vector2f get_loadedGamerPos();																						//Odczyt pozycji gracza z pliku
	sf::Vector2f get_loadedLavaPos();																						//Odczyt pozycji lawy z pliku
	unsigned int get_loadeddiamonds();																						//Odczyt zebranych diamentw z pliku
	unsigned int get_loadediron();																							//Odczyt zebranego elaza z pliku
	unsigned int get_loadedDifficulty();																					//Odczyt poziomu trudnoci z pliku
};