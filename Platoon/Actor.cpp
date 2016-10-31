#include "Actor.h"

Actor::Actor(string fileName)
{
	//General Attributes
	renderObject = new RenderObject(fileName);
	renderObject->sprite.setOrigin(renderObject->sprite.getLocalBounds().width / 2.5f, renderObject->sprite.getLocalBounds().height / 3);
	renderObject->sprite.scale(0.2f, 0.2f);

	//BoundingCirlce
	float biggerside = renderObject->sprite.getGlobalBounds().width;
	if (renderObject->sprite.getGlobalBounds().height > biggerside) biggerside = renderObject->sprite.getGlobalBounds().height;
	boundingCircle = new sf::CircleShape(biggerside / 2);
	boundingCircle->setPosition(sf::Vector2f(renderObject->sprite.getPosition().x - renderObject->sprite.getGlobalBounds().width / 2, renderObject->sprite.getPosition().y - renderObject->sprite.getGlobalBounds().height / 2));

	//Moving related
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	maxSpeed = 3.0f;
	steeringForce = 0.2f;
	arrivalRadius = 50.0f;;

	//trajectory
	timeSincePoint = 0.0f;

	//Hardcoded Target
	target.x = 800.0f;
	target.y = 800.0f;
	targettype = 0;
	ToggleTargetType();
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
	//Bind in screen
	if (pos.x < 0) pos.x = 0;
	if (pos.y < 0) pos.y = 0;
	if (pos.x > 1000) pos.x = 1000;
	if (pos.y > 1000) pos.y = 1000;

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
	for(auto i : trajectory)
	{
		window->draw(i);
	}
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
	targetshape.setRadius(2);
	targetshape.setPosition(target.x - targetshape.getRadius(), target.y - targetshape.getRadius());

	window->draw(targetshape);
}

void Actor::Move(sf::Time deltaTime)
{
	timeSincePoint += deltaTime.asSeconds();
	if(timeSincePoint > 0.25f)
	{
		MarkPosition();
		timeSincePoint = 0.0f;
	}

	glm::vec2 steering;
	
	switch(targettype)
	{
	case 1:
		steering = Seek(velocity, target);
		break;
	case 2:
		steering = Arrive(velocity, target);
		break;
	case 3:
		steering = Flee(velocity, target);
		break;
	default:
		break;
	}

	velocity = (velocity + steering);
	velocity = truncate(velocity, maxSpeed) ;
	if ((velocity.x < -0.00001f || velocity.x > 0.00001f) && (velocity.y < -0.00001f || velocity.y > 0.00001f))
	{
		setPosition(position + velocity);
	}
}

glm::vec2 Actor::Seek(const glm::vec2 currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = glm::normalize(currentTarget - position) * maxSpeed;
	glm::vec2 newSteering = desiredVelocity - currentVelocity;

	newSteering = truncate(newSteering, steeringForce);

	return newSteering;
}

glm::vec2 Actor::Flee(const glm::vec2 currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = glm::normalize(position - currentTarget) * maxSpeed;
	glm::vec2 newSteering = desiredVelocity - currentVelocity;

	newSteering = truncate(newSteering, steeringForce);

	return newSteering;
}

glm::vec2 Actor::Arrive(const glm::vec2 currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = currentTarget - position;
	float distance = glm::distance(currentTarget, position);

	if(distance < arrivalRadius)
	{
		desiredVelocity = glm::normalize(desiredVelocity) * maxSpeed * (distance / arrivalRadius);
	} else
	{
		desiredVelocity = glm::normalize(desiredVelocity) * maxSpeed;
	}

	glm::vec2 newSteering;
	newSteering = desiredVelocity - currentVelocity;
	
	newSteering = truncate(newSteering, steeringForce);

	return newSteering;
}

glm::vec2 Actor::truncate(glm::vec2 totrunc, float max)
{
	float i = max / glm::length(totrunc);
	if(i > 1.0f)
	{
		i = 1.0f;
	}

	return totrunc * i;
}

void Actor::MarkPosition()
{
	if(trajectory.size() > 25)
	{
		trajectory.erase(trajectory.begin());
	}
	
	sf::CircleShape newpoint;
	newpoint.setPosition(position.x, position.y);
	newpoint.setRadius(5.0f);
	newpoint.setFillColor(sf::Color(180, 40, 40, 120));

	trajectory.push_back(sf::CircleShape(newpoint));
}

void Actor::ToggleTargetType()
{
	targettype++;
	if (targettype > 3) targettype = 1;

	switch (targettype)
	{
	case 1:
		cout << "Where is that bastard..." << endl;
		break;
	case 2:
		cout << "There he is!" << endl;
		break;
	case 3:
		cout << "OMG! RUN FOR YOUR LIFES!!" << endl;
		break;
	default:
		break;
	}
}
