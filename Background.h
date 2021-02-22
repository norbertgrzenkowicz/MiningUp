#pragma once

#include "Lava.h"
class Background
{
private:
	//T�o szare
	sf::RectangleShape* background;
	//t�o za graczem
	sf::Sprite* gameBackground;
	sf::Texture backgroundTexture;
	//Outline �rodowiska gry
	sf::RectangleShape* gameOutline;
public:
	Background(sf::Vector2u window);
	~Background();

	void drawBackground(sf::RenderWindow& window);		//rysowanie szarego t�a
	void drawGameBackground(sf::RenderWindow& window);	//rysowanie t�a za graczaem
};