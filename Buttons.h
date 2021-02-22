#include "Myszka.h"
class Buttons
{
private:
	
	sf::Font font; //czcionka

	//Elementy przycisku
	sf::RectangleShape* button;
	sf::RectangleShape* obramowanie;
	sf::FloatRect* buttonBounds;
	sf::Sprite* buttonSprite;
	
	//Elementy tekstu
	sf::Text* tekst;
	sf::FloatRect* tekstBounds;
	std::string tresc;
	
	//Pozycje
	sf::Vector2f mousePos;
	sf::Vector2f buttonPos;

	//tekstury
	sf::Texture stopTexture, backtogameTexture, renewTexture, backtomenuTexture, pickaxeT;

	//Sprite kilofu do menu wyboru poziomu trudnoœci
	sf::Sprite pickaxe;


public:
	bool Pause;
	Buttons();
	Buttons(int whichButton, sf::RenderWindow& window); //Konstruktor wszystkich przycisków, whichButton wskazuje jaki przycisk ma zostaæ przywo³any

	~Buttons();
	bool isClicked(sf::Event& event, sf::RenderWindow& window); //Metoda sprawdzaj¹ca czy przycisk zosta³ klikniêty, rysuje szary element na przycisku jeœli myszka jest wewn¹trz przycisku
	void draw(sf::RenderWindow& window);						//rysowanie przycisków i tekstu
	void drawSprites(sf::RenderWindow& window);					//rysowanie kilofów
};