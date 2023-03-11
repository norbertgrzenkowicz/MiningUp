#include "Myszka.h"
#include "Entity.h"

class Buttons : public Entity_iface
{
private:
	
	sf::Font font; //czcionka

	//Elementy przycisku
	sf::RectangleShape button;
	sf::RectangleShape obramowanie;
	sf::FloatRect* buttonBounds;
	sf::Sprite* buttonSprite;
	
	//Elementy tekstu
	sf::Text* tekst;
	sf::FloatRect tekstBounds;
	std::string tresc;
	
	//Pozycje
	sf::Vector2f mousePos;
	sf::Vector2f buttonPos;

	//tekstury
	sf::Texture stopTexture, backtogameTexture, renewTexture, backtomenuTexture, pickaxeT;

	//Sprite kilofu do menu wyboru poziomu trudnoci
	sf::Sprite pickaxe;


public:
	Buttons();
	Buttons(int whichButton, sf::RenderWindow& window); //Konstruktor wszystkich przyciskow, whichButton wskazuje jaki przycisk ma zostal przywolany

	~Buttons();
	bool isClicked(sf::Event& event, sf::RenderWindow& window); //Metoda sprawdzajaca czy przycisk zostal klikniety, rysuje szary element na przycisku jesli myszka jest wewnatrz przycisku
	void draw(sf::RenderWindow& window) final;						//rysowanie przyciskow i tekstu
	void drawSprites(sf::RenderWindow& window);					//rysowanie kilofow
};
