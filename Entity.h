#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Entity_iface
{
public:
	virtual ~Entity_iface() = default;

	virtual void draw(sf::RenderWindow& window) = 0;
};