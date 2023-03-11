#pragma once

#include "Lava.h"

#include "Entity.h"

class Background : public Entity_iface
{
private:
	//Tlo szare
	sf::RectangleShape* background;
	//tlo za graczem
	sf::Sprite* gameBackground;
	sf::Texture backgroundTexture;
	//Outline srodowiska gry
	sf::RectangleShape* gameOutline;
public:
	Background(sf::Vector2u window);
	~Background();

	void drawBackground(sf::RenderWindow& window);		//rysowanie szarego tla
	void draw(sf::RenderWindow& window) final;	//rysowanie tla za graczaem
};
