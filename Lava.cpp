#include "Lava.h"

Lava::Lava()
{
	//Inicjalizacja ruchu oraz rozmiaru
	yMove = 0;
	ySize = 0;

	//lavaSurface = new sf::Sprite;
	restOfLava = new sf::RectangleShape;
	lavaSurface = new sf::RectangleShape;

	//wczytywanie tekstury
	if (!lavaT.loadFromFile("textures/lava.png"))
		std::cout<<"Nie udalo sie wczytac tekstury!";

	//cechy graficzne oraz po³o¿enia lawy
	lavaSurface->setTexture(&lavaT);
	//lavaSurface->setScale(7.5f, 10.f);
	lavaSurface->setSize(sf::Vector2f(1080.f, 240.f));
	lavaSurface->setPosition(360.f, 1020.f);
	lavish = sf::Color(194, 70, 17);
	restOfLava->setFillColor(lavish);
	restOfLava->setPosition(360.f, lavaSurface->getPosition().y+240);
}

Lava::~Lava()
{
	delete lavaSurface, restOfLava;
}

void Lava::moveUp(const float &dt)
{
	yMove = 8 * dt * difficultyMultiplier;
	ySize += yMove;
	restOfLava->setSize(sf::Vector2f(1080, 250+ySize));
	lavaSurface->move(0, -yMove);
	restOfLava->move(0, -yMove);
}

void Lava::draw(sf::RenderWindow& window)
{
	window.draw(*restOfLava);
	window.draw(*lavaSurface);
}

sf::Vector2f Lava::getLavaSurfacePos()
{
	return lavaSurface->getPosition();
}
void Lava::setPositionDefault()
{
	restOfLava->setPosition(360.f, lavaSurface->getPosition().y + 240);
}
void Lava::setPosition(sf::Vector2f lavaPos)
{
	lavaSurface->setPosition(sf::Vector2f(lavaPos.x, lavaPos.y));
	restOfLava->setPosition(360.f, lavaSurface->getPosition().y + 240);
}

void Lava::setDifficultyMultiplier(unsigned int difficulty)
{
	if (difficulty == 1 || difficulty == 2)
	{
		difficultyMultiplier = 1.f;
	}
	else if (difficulty == 3)
	{
		difficultyMultiplier = 1.3f;
	}
}

void Lava::isTileDown(bool istiledown)
{
	if (istiledown == true)
		this->setPosition(sf::Vector2f(lavaSurface->getPosition().x, lavaSurface->getPosition().y + 60.f));
	restOfLava->setPosition(lavaSurface->getPosition().x, lavaSurface->getPosition().y + 240);
}