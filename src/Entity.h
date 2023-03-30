#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Entity_iface
{
  public:
    virtual ~Entity_iface() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
};
