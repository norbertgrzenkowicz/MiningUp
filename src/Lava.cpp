#include "Lava.h"

Lava::Lava(const sf::Vector2u& window) :
	yMove(0),
	ySize(0)
{
	//Inicjalizacja ruchu oraz rozmiaru

	//lavaSurface = new sf::Sprite;
	// restOfLava = std::make_unique<sf::RectangleShape>();
	// lavaSurface = std::make_unique<sf::RectangleShape>();
	lavaT = std::make_unique<sf::Texture>();
	//wczytywanie tekstury
	if (!lavaT->loadFromFile("textures/lava.png"))
		std::cout<<"Nie udalo sie wczytac tekstury!";

	//cechy graficzne oraz po�o�enia lawy
	lavaSurface.setTexture(lavaT.get());
	//lavaSurface.setScale(7.5f, 10.f);
	lavaSurface.setSize(sf::Vector2f(window.y, window.y / 4.5f));
	lavaSurface.setPosition(GAME_WINDOW_START, window.y - 60.f);
	lavish = sf::Color(194, 70, 17);
	restOfLava.setFillColor(lavish);
	restOfLava.setPosition(GAME_WINDOW_START, lavaSurface.getPosition().y+240);
}

void Lava::moveUp(const float &dt)
{
	yMove = 8 * dt * difficultyMultiplier;
	ySize += yMove;
	restOfLava.setSize(sf::Vector2f(FULL_HD_HEIGHT, 250+ySize));
	lavaSurface.move(0, -yMove);
	restOfLava.move(0, -yMove);
}

void Lava::draw(sf::RenderWindow& window)
{
	window.draw(restOfLava);
	window.draw(lavaSurface);
}

sf::Vector2f Lava::getLavaSurfacePos()
{
	return lavaSurface.getPosition();
}
void Lava::setPositionDefault()
{
	restOfLava.setPosition(GAME_WINDOW_START, lavaSurface.getPosition().y + 240);
}

void Lava::setPosition(sf::Vector2f lavaPos)
{
	lavaSurface.setPosition({lavaPos.x, lavaPos.y});
	restOfLava.setPosition(GAME_WINDOW_START, lavaSurface.getPosition().y + 240);
}

void Lava::setDifficultyMultiplier(unsigned int difficulty)
{
	difficultyMultiplier = (difficulty == 3 && difficulty <= 3) ? EASYANDMIDDIFF : HARDDIFF;
}

void Lava::isTileDown(bool istiledown)
{
	if (istiledown == true)
		this->setPosition({lavaSurface.getPosition().x, lavaSurface.getPosition().y + 60.f});

	restOfLava.setPosition(lavaSurface.getPosition().x, lavaSurface.getPosition().y + 240);
}
