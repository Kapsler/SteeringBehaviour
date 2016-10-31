#include "Actor.h"

Actor::Actor(string fileName)
{
	//General Attributes
	renderObject = new RenderObject(fileName);
	renderObject->sprite.setOrigin(renderObject->sprite.getLocalBounds().width / 2.5f, renderObject->sprite.getLocalBounds().height / 3);
	renderObject->sprite.scale(0.5f, 0.5f);

	//BoundingCirlce
	float biggerside = renderObject->sprite.getGlobalBounds().width;
	if (renderObject->sprite.getGlobalBounds().height > biggerside) biggerside = renderObject->sprite.getGlobalBounds().height;
	boundingCircle = new sf::CircleShape(biggerside / 2);
	boundingCircle->setPosition(sf::Vector2f(renderObject->sprite.getPosition().x - renderObject->sprite.getGlobalBounds().width / 2, renderObject->sprite.getPosition().y - renderObject->sprite.getGlobalBounds().height / 2));

	//Moving related
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	maxSpeed = 300.0f;
	turnRadius = 0.0005f;

	//Hardcoded Target
	target.x = 800.0f;
	target.y = 800.0f;
	//Target end
}

Actor::Actor(const Actor&)
{
}

Actor::~Actor()
{
	delete boundingCircle;
	boundingCircle = nullptr;

	delete renderObject;
	renderObject = nullptr;
}

void Actor::setPosition(glm::vec2 pos)
{
	position = pos;
	renderObject->setPosition(pos);
	boundingCircle->setPosition(sf::Vector2f(position.x - renderObject->sprite.getGlobalBounds().width / 2, position.y - renderObject->sprite.getGlobalBounds().height / 2));
}

glm::vec2 Actor::getPosition()
{
	return position;
}

bool Actor::Intersect(sf::CircleShape* circle)
{
	return false;
}

bool Actor::Intersect(sf::FloatRect* rect)
{
	return false;
}

void Actor::Render(sf::RenderWindow* window)
{
	renderObject->Render(window);
}

void Actor::DebugDraw(sf::RenderWindow* window)
{
	//Debug Fill Color
	boundingCircle->setFillColor(sf::Color(180, 40, 40, 120));
	window->draw(*boundingCircle);
	boundingCircle->setFillColor(sf::Color::Transparent);

	//Target follow mouse
	sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	target.x = mouse.x;
	target.y = mouse.y;

	//End following

	sf::CircleShape targetshape;
	targetshape.setPosition(target.x, target.y);
	targetshape.setRadius(10);

	window->draw(targetshape);
}

void Actor::Move(sf::Time deltaTime)
{
	glm::vec2 steering = Seek(velocity, target);

	velocity = glm::normalize(velocity + steering) * maxSpeed * deltaTime.asSeconds();
	if (velocity.x != 0 && velocity.y != 0)
	{
		setPosition(position + velocity);
	}
}


glm::vec2 Actor::Seek(const glm::vec2 currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = currentTarget - position;
	glm::vec2 newSteering = desiredVelocity - currentVelocity;

	newSteering = glm::normalize(newSteering) * turnRadius;

	return newSteering;
}
