#pragma once
#include "SFML/Graphics.hpp"

class Collidable
{
public:
	Collidable();
	virtual ~Collidable();

	virtual bool Intersect(sf::CircleShape* circle) = 0;
	virtual bool Intersect(sf::FloatRect* rect) = 0;

};
