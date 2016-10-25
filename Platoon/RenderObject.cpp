#include "RenderObject.h"

RenderObject::RenderObject(string fileName)
{
	if (!texture.loadFromFile(fileName))
	{
		cerr << "Coudln't load texture " << fileName << std::endl;
		//texture.loadFromFile("");
	}
	texture.setSmooth(true);
	texture.setRepeated(false);
	sprite.setTexture(texture);
}

RenderObject::RenderObject(const RenderObject& other)
{
}

RenderObject::~RenderObject()
{
}

void RenderObject::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}
