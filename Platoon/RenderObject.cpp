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

	boundingbox.setSize(sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	boundingbox.setOrigin(boundingbox.getSize().x / 2, boundingbox.getSize().y / 2);
	boundingbox.setPosition(sprite.getPosition());

	boundingbox.setFillColor(sf::Color(40, 40, 120, 120));
}

RenderObject::RenderObject(std::string fileName, glm::vec2 pos) : RenderObject(fileName)
{
	SetPosition(pos);
}

RenderObject::RenderObject(const RenderObject& other)
{
}

RenderObject::~RenderObject()
{
}

void RenderObject::SetPosition(glm::vec2 pos)
{
	sprite.setPosition(pos.x, pos.y);
	boundingbox.setPosition(pos.x, pos.y);
}

void RenderObject::SetRotation(float rot)
{
	sprite.setRotation(rot);
	boundingbox.setRotation(rot);
}

void RenderObject::SetScale(float x, float y)
{
	sprite.setScale(x, y);
	boundingbox.setScale(x, y);
}

void RenderObject::Scale(float x, float y)
{
	sprite.scale(x, y);
	boundingbox.scale(x, y);
}

void RenderObject::Rotate(float rot)
{
	sprite.rotate(rot);
	boundingbox.rotate(rot);
}

sf::RectangleShape RenderObject::GetBoundingBox() const
{
	return boundingbox;
}

void RenderObject::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void RenderObject::DebugDraw(sf::RenderWindow* window)
{

}
