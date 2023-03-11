#pragma once

#include "Entity.h"

class Positionable : public Entity_iface
{
public:
	virtual void draw(sf::RenderWindow& window) override {};
	virtual void setPosition(sf::Vector2f entityPos) = 0;
	virtual void setPositionDefault() = 0;
};
