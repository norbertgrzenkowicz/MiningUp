#pragma once
#include "Camera.h"
#include "Positionable.h"
class Lava : public Positionable
{
private:
	//Cechy graficzne lawy
	sf::Texture lavaT;
	//sf::Sprite* lavaSurface;
	sf::RectangleShape* lavaSurface;
	sf::RectangleShape* restOfLava;
	sf::Color lavish;

	//cechy ruchu oraz rozmiaru
	float yMove;
	float ySize;
	
	//mnonik poziomu trudnoci, zwiksza bd zwiksza prdko poruszania si lawy
	unsigned int difficultyMultiplier;
	
public:
	Lava();
	~Lava();

	void moveUp(const float &dt);								//Cykliczny ruch lawy do gry wzgldem prdkoci i czasu
	void draw(sf::RenderWindow& window) final;						//Rysowanie lawy
	sf::Vector2f getLavaSurfacePos();							//Zwraca poziom lawy
	void setPositionDefault() final;									//Ustawia pozycj pocztkow
	void setPosition(sf::Vector2f entityPos) final;						//Ustawia pozycj lawy oraz dolnej czci lawy
	void setDifficultyMultiplier(unsigned int difficulty);		//Ustawia mnonik poziomu trudnoci
	void isTileDown(bool istiledown);							//zmienia pozycj ze wzgldu na wykonanie funkcji TileMap::tileDown()
};