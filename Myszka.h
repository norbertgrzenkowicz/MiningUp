#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>


class Myszka
{
private:
	
	//zasieg postaci
	float destroyRange;

	//Pozycjonowanie myszki
	sf::Font font;
	float gridSizef;
	int gridSizeU;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Pozycjonowanie zaznaczonego kafla
	sf::Vector2u rangeLimitGridPos;
	sf::Vector2u BetweentileGridPos;
	sf::Vector2f rangeLimit;
	sf::Vector2f rangeLimitHalfed;
	
	//pozycjonowanie srodka gracza
	sf::Vector2f gamerPosMid; 
	//TileSelector
	sf::RectangleShape* tileSelector;

	//Pomocniczy wyznacznik zasiegu
	sf::RectangleShape* testBox;
	sf::RectangleShape* testBoxHalfed;

	//Pomocniczy tekst koordynatow myszki
	sf::Text text;
public:
	Myszka();
	~Myszka();

	void positioning(sf::RenderWindow& window, sf::Vector2f gamerPos, sf::FloatRect gamerBounds); //Kompletna metoda pozycjonowania myszki oraz kafli wzgledem zasiegu postaci
	void draw(sf::RenderWindow& window); //rysowanie wszystkich elementow
	void isTileBetween(); //pozycjonuje tileSelector do kalfa pomiedzy wskazanym kaflem 
	sf::Vector2u gettileSelectorGridPos(); //zwracanie pozycji tileSelectora
	sf::Vector2u getBetweentileGridPos(); //zwracanie pozycji kafla pomiedzy wskazanym kaflem
	sf::Text getText(); //zwracanie tekstu koordynatow myszki
};
