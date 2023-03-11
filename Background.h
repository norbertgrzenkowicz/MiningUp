#pragma once

#include "Lava.h"

#include "Entity.h"

class Background : public Entity_iface
{
public:
	Background(sf::Vector2u window, std::string&& backgroundTexturePath);

	void drawBackground(sf::RenderWindow& window);		//rysowanie szarego tla
	void draw(sf::RenderWindow& window) final;	//rysowanie tla za graczaem

private:
	//Tlo szare
	sf::RectangleShape background;
	//tlo za graczem
	std::unique_ptr<sf::Sprite> gameBackground;
	sf::Texture backgroundTexture;
	//Outline srodowiska gry
	sf::RectangleShape gameOutline;
};
