#pragma once
#include <SFML/Graphics.hpp>

class Renderable
{
public:
	Renderable();
	virtual ~Renderable();

	virtual void Render(sf::RenderWindow* window) = 0;
	virtual void DebugDraw(sf::RenderWindow* window) = 0;
};
