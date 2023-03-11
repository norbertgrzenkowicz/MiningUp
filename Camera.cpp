#include "Camera.h"


Camera::Camera(sf::Vector2u window)
{
	view = new sf::View;
	view->setSize(window.x, window.y); //Inicjalizacja rozmiaru kamery
}

Camera::~Camera()
{
	delete view;
}

void Camera::followplayer(sf::RenderWindow& window, sf::Vector2f playerPos, sf::FloatRect playerBounds, bool lavaTouched)
{
	if (lavaTouched != true) //pki gracz jest ywy
		view->setCenter(960.f, playerPos.y + playerBounds.height); //Kamera jest wyrodkowana na graczu w osi Y

	window.setView(*view);
}
