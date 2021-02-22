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
	
	//mno¿nik poziomu trudnoœci, zwiêksza b¹dŸ zwiêksza prêdkoœæ poruszania siê lawy
	unsigned int difficultyMultiplier;
	
public:
	Lava();
	~Lava();

	void moveUp(const float &dt);								//Cykliczny ruch lawy do góry wzglêdem prêdkoœci i czasu
	void draw(sf::RenderWindow& window);						//Rysowanie lawy
	sf::Vector2f getLavaSurfacePos();							//Zwraca poziom lawy
	void setPositionDefault();									//Ustawia pozycjê pocz¹tkow¹
	void setPosition(sf::Vector2f lavaPos);						//Ustawia pozycjê lawy oraz dolnej czêœci lawy
	void setDifficultyMultiplier(unsigned int difficulty);		//Ustawia mno¿nik poziomu trudnoœci
	void isTileDown(bool istiledown);							//zmienia pozycjê ze wzglêdu na wykonanie funkcji TileMap::tileDown()
};