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


void RenderObject::Render(sf::RenderWindow* window)
{
	window->draw(sprite);
}

void RenderObject::DebugDraw(sf::RenderWindow* window)
{
	/*float biggerside = sprite.getGlobalBounds().width;
	if (sprite.getGlobalBounds().height > biggerside) biggerside = sprite.getGlobalBounds().height;
	sf::RectangleShape box(sf::Vector2<float>(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
	box.setPosition(sf::Vector2<float>(sprite.getPosition().x - sprite.getGlobalBounds().width/2, sprite.getPosition().y - sprite.getGlobalBounds().height / 2));
	sf::CircleShape circle(biggerside / 2);
	circle.setPosition(sf::Vector2<float>(sprite.getPosition().x - sprite.getGlobalBounds().width / 2, sprite.getPosition().y - sprite.getGlobalBounds().height / 2));
	circle.setFillColor(sf::Color::Black);
	window->draw(box);
	window->draw(circle);*/
}
