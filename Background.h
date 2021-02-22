#pragma once

#include "Lava.h"
class Background
{
private:
	//T³o szare
	sf::RectangleShape* background;
	//t³o za graczem
	sf::Sprite* gameBackground;
	sf::Texture backgroundTexture;
	//Outline œrodowiska gry
	sf::RectangleShape* gameOutline;
public:
	Background(sf::Vector2u window);
	~Background();

	void drawBackground(sf::RenderWindow& window);		//rysowanie szarego t³a
	void drawGameBackground(sf::RenderWindow& window);	//rysowanie t³a za graczaem
};