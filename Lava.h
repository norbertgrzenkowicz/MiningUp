#pragma once
#include "Camera.h"

class Lava
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
	
	//mno�nik poziomu trudno�ci, zwi�ksza b�d� zwi�ksza pr�dko�� poruszania si� lawy
	unsigned int difficultyMultiplier;
	
public:
	Lava();
	~Lava();

	void moveUp(const float &dt);								//Cykliczny ruch lawy do g�ry wzgl�dem pr�dko�ci i czasu
	void draw(sf::RenderWindow& window);						//Rysowanie lawy
	sf::Vector2f getLavaSurfacePos();							//Zwraca poziom lawy
	void setPositionDefault();									//Ustawia pozycj� pocz�tkow�
	void setPosition(sf::Vector2f lavaPos);						//Ustawia pozycj� lawy oraz dolnej cz�ci lawy
	void setDifficultyMultiplier(unsigned int difficulty);		//Ustawia mno�nik poziomu trudno�ci
	void isTileDown(bool istiledown);							//zmienia pozycj� ze wzgl�du na wykonanie funkcji TileMap::tileDown()
};