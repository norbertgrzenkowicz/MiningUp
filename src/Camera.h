#pragma once

#include "player.h"

class Camera
{
public:
	Camera(sf::Vector2u window);

	void followplayer(sf::RenderWindow& window, sf::Vector2f playerPos, sf::FloatRect playerBounds, bool lavaTouched); //Kamera podajca za graczem w osi Y

private:
	std::unique_ptr<sf::View> view; //Zmienna widoku
};
