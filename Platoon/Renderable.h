#pragma once
#include <SFML/Graphics.hpp>

class Renderable
{
public:
	Renderable();
	virtual ~Renderable();

	virtual void Render(sf::RenderWindow* window) = 0;

	sf::Texture texture; 
	sf::Sprite sprite;
};
