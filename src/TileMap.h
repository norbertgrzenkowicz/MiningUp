#include "UserInterface.h"

class TileMap
{
public:
	TileMap();

	void generateTiles();																			//generowanie losowe rodzai kafli
	void map();																						//Wzgledem vectora typ_kafli narzucane sa odpowiednie kafle do vectora tileMap
	void destroyTile(const float& dt, sf::Event& event);											//niszczenie kafli
	sf::Vector2f tilesDown(sf::Vector2f playerPos);													//Dodawanie kolejnej warstwy kafli przesuwajac istniejace
	void ChangeTile();																				//Wywolanie metody isTileBetween() klasy Myszka
	void positioning(sf::RenderWindow& window, sf::Vector2f gamerPos, sf::FloatRect gamerBounds);	//wywolanie funkcji positioning() klasy Myszka
	void animateDestroying(const float& dt, int y, int x);	
	void setDifficultyMultiplier(unsigned int difficulty);
	void countDiamonds();																			//Liczenie uzyskanych diamentow
	unsigned int getGatheredDiamonds();																//zwracanie zebranych diamentow
	void setDiamonds(unsigned int diamonds);														//wczytywanie diamentow z pliku
	void setDiamondsDefault();																		//ustawianie diamentow do liczby 0
	void countIron();																				//Liczenie uzyskanego zelaza
	void setIron(unsigned int iron);																//wczytywanie zelaza z pliku
	void setIronDefault();																			//ustawianie zelaza do liczby 0
	unsigned int getGatheredIron();																	//zwracanie zebranego zelaza

	
	void set_typ_kafli(std::vector<std::vector<int>> loadedTypy_kafli);								//ustawianie typow kafli z pliku
	std::vector<std::vector<int>> get_typ_kafli();													//zwracanie typy kafli
	std::vector<std::vector<sf::RectangleShape>> gettileMap();										//zwracanie calej tileMapy
	bool get_isTileDown();																			//zwracanie wartosci czy zostala wykonana funkcja tilesDown()
	sf::Text getText();																				//nadpisanie funkcji getText() klasy Myszka
	void drawDestroyAnimation(sf::RenderWindow& window);											//rysowanie animacji niszczenia klockow
	void draw(sf::RenderWindow& window);															//rysowanie wszystkich elementow 

private:
	Myszka myszka;

	//Zmienne czasu kopania
	float elapsed;	
	float miningTime;
	float ironMiningTime;
	float diamondMiningTime;
	float stoneMiningTime;
	
	//wielkosc rozmiaru siatki mapy
	float gridSizeF;
	//zmienna liczaca czas wzgledem zmiennej dt
	float dtime;

	//mnoznik zalezny od wybranej trudnosci, wplywa na szybkosc wydobywania
	float difficultyMultiplier;

	//rozmiary mapy
	const static int mapSizeY = 22;
	const static int mapSizeX = 18;

	//zmienna pomocnicza do sprawdzania czy kopany jest ten sam blok
	int isItSameBlock;

	//zmienne zebranych surowcow
	unsigned int gatheredDiamonds;
	unsigned int gatheredIron;
	
	//Bazowa pozycja gracza w siatce 
	int pastPlayerGridPos = 12;

	bool isTileDown;

	//tekstury kafli
	sf::Texture diamond;
	sf::Texture stone;
	sf::Texture iron;
	sf::Texture destroying;
	
	//Zmienne animacji niszczenia kafli
	sf::Sprite destroyingTiles;
	sf::IntRect rectDestroying;


	//2D vectory typu kafli wystepujacych oraz konkretnych prostokatow z teksturami
	std::vector<std::vector<int>> typ_kafli;
	std::vector<std::vector<sf::RectangleShape>> tileMap;
};
