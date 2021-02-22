#pragma once

#include "player.h"

class Camera
{
private:
	sf::View* view; //Zmienna widoku
public:
	Camera(sf::Vector2u window);
	~Camera();

	void followplayer(sf::RenderWindow* window, sf::Vector2f playerPos, sf::FloatRect playerBounds, bool lavaTouched); //Kamera pod¹¿aj¹ca za graczem w osi Y
};