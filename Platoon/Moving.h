#pragma once
#include <SFML/Graphics.hpp>


class Moving
{
public: 
	Moving();
	virtual ~Moving();

	virtual void Move(sf::Time delta) = 0;
};
