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

	//Sprite kilofu do menu wyboru poziomu trudno�ci
	sf::Sprite pickaxe;


public:
	bool Pause;
	Buttons();
	Buttons(int whichButton, sf::RenderWindow& window); //Konstruktor wszystkich przycisk�w, whichButton wskazuje jaki przycisk ma zosta� przywo�any

	~Buttons();
	bool isClicked(sf::Event& event, sf::RenderWindow& window); //Metoda sprawdzaj�ca czy przycisk zosta� klikni�ty, rysuje szary element na przycisku je�li myszka jest wewn�trz przycisku
	void draw(sf::RenderWindow& window);						//rysowanie przycisk�w i tekstu
	void drawSprites(sf::RenderWindow& window);					//rysowanie kilof�w
};