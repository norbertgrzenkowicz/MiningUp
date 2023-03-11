#include "Menu.h"

#define MAX_SAVES 5
#define SAVE_FILE_LENGTH 29
#define GAME_WINDOW_START FULL_HD_HEIGHT / 3
#define FULL_HD_HEIGHT 1080.f
#define FULL_HD_WIDTH 1920.f

class UserInterface
{
public:
	std::unique_ptr<Menu> menu;
	UserInterface(sf::RenderWindow& window);

	void inGameUI(sf::Event& event, sf::RenderWindow& window, unsigned int diamondsCounted, unsigned int ironCounted);		//Interfejs gracza podczas gry
	void helpMenu(sf::Event& event, sf::RenderWindow& window);																//help Menu
	bool endGameMenu(const bool isDead, sf::Event& event, sf::RenderWindow& window);												//Menu pomiertne
	void playersScore(sf::Event& event, sf::RenderWindow& window);															//Menu statystyk graczy
	void chooseDifficulty(sf::Event& event, sf::RenderWindow& window);														//Menu wyboru poziomu trudnoci

	void save(sf::Vector2f&& playerPos, std::vector<std::vector<int>>&& tilemap, sf::Vector2f&& lavaPos, unsigned int diamondsCount, unsigned int ironCount); //Zapis gry
	void savePlayers(const unsigned int diamondsCount, unsigned int ironCount, unsigned int difficulty);							//Zapis statystyk graczy
	void saveDead(unsigned int diamondsCount, unsigned int ironCount, unsigned int difficulty);								//Zapis statystyk po mierci
	void loadGame();																										//Odczyt gry
	void loadPlayers();																										//Odczyt graczy

	void putShadow(sf::RenderWindow& window);																				//Zaciemienie gry na czas pauzy/helpMenu
	void leaveQuestion(sf::Event& event, sf::RenderWindow& window);															//Zapytanie czy chcesz wyjsc z gry

	void set_escape(const bool esc);																								//Ustawianie booleanu zapytania wyjcia z gry
	void set_renew(const bool renewG);																							//Ustawianie booleanu odnowienia gry
	bool get_renew();																										//Odczyt booleanu odnowienia gry
	void set_difficulty(const unsigned int difficulty);																			//Ustawianie poziomu trudnoci gry
	unsigned int get_difficulty();																							//Odczyt poziomu trudnoci gry
	void set_Pause(const bool Pause);

	std::vector<std::vector<int>> get_loadedTypy_kafli();																	//Odczyt typy_kafli z pliku
	sf::Vector2f get_loadedGamerPos();																						//Odczyt pozycji gracza z pliku
	sf::Vector2f get_loadedLavaPos();																						//Odczyt pozycji lawy z pliku
	unsigned int get_loadeddiamonds();																						//Odczyt zebranych diamentw z pliku
	unsigned int get_loadediron();																							//Odczyt zebranego elaza z pliku
	unsigned int get_loadedDifficulty();																					//Odczyt poziomu trudnoci z pliku
	bool get_Pause();

private:
	//Zmienne pomocnicze stanw gry
	bool Pause;
	bool renew;
	bool helpMenuBool;
	bool isSaved;
	bool isLoaded;
	bool escape;

	std::string helptext;
	unsigned int difficulty;

	//Tekstura licznikw surowcw
	sf::Texture countUIT;
	sf::Sprite countUI;

	sf::Font font;

	//Tekst
	sf::Text diamonds;
	sf::Text iron;
	sf::Text playerNumber;
	sf::Text difficultyText;
	sf::Text naglowek;
	sf::Text kategorie;
	sf::Text helpText;
	sf::Text escBack;
	sf::Text leave;
	sf::Text gameOver;

	//Przyciski
	std::unique_ptr<Buttons> przyciskStop;
	std::unique_ptr<Buttons> przyciskBackToGame;
	std::unique_ptr<Buttons> przyciskRenew;
	std::unique_ptr<Buttons> przyciskBackToMenu;
	std::unique_ptr<Buttons> endGameBackToMenu;
	std::unique_ptr<Buttons> yesButton;
	std::unique_ptr<Buttons> noButton;
	std::unique_ptr<Buttons> easyButton;
	std::unique_ptr<Buttons> mediumButton;
	std::unique_ptr<Buttons> hardButton;

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
};
