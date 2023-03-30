#include "Camera.h"

Camera::Camera(sf::Vector2u window)
{
    view = std::make_unique<sf::View>();
    view->setSize(window.x, window.y);   // Inicjalizacja rozmiaru kamery
}

void Camera::followplayer(sf::RenderWindow& window, sf::Vector2f playerPos, sf::FloatRect playerBounds, bool lavaTouched)
{
    if (!lavaTouched)                                                // pki gracz jest zywy
        view->setCenter(960.f, playerPos.y + playerBounds.height);   // Kamera jest wyrodkowana na graczu w osi Y

    window.setView(*view);
}
