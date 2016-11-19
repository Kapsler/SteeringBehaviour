#include "RenderObject.h"

RenderObject::RenderObject(string fileName)
{
	if (!texture.loadFromFile(fileName))
	{
		cerr << "Coudln't load texture " << fileName << std::endl;
		texture.loadFromFile("./Assets/missing.jpg");
	}
	texture.setSmooth(true);
	texture.setRepeated(false);
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

RenderObject::RenderObject(std::string fileName, glm::vec2 pos) : RenderObject(fileName)
{
	setPosition(pos);
}

RenderObject::RenderObject(const RenderObject& other)
{
}

RenderObject::~RenderObject()
{
}

void RenderObject::setPosition(glm::vec2 pos)
{
	sprite.setPosition(pos.x, pos.y);
}

void RenderObject::setRotation(float rot)
{
	sprite.setRotation(rot);
}

sf::FloatRect RenderObject::GetBoundingBox()
{
	return sprite.getGlobalBounds();
}

void RenderObject::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void RenderObject::DebugDraw(sf::RenderWindow* window)
{
}
