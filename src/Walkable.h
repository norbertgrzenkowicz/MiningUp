#pragma once

#include "Positionable.h"

class Walkable : public Positionable
{
    // virtual ~Walkable() = default;
  public:
    virtual void draw(sf::RenderWindow& window) override {};
    virtual void setPosition(sf::Vector2f entityPos) override {};
    virtual void setPositionDefault() override {};
    virtual void wallCollision() = 0;
    virtual void objectCollision(sf::RectangleShape wall) = 0;
    virtual void physics() = 0;
};
