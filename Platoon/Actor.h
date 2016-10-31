#pragma once
#include "RenderObject.h"
#include "Collidable.h"
#include "Moving.h"
#include <glm/glm.hpp>

class Actor : public Renderable, public Collidable, public Moving
{
public:
	Actor(string fileName);
	Actor(const Actor&);
	~Actor();

	void setPosition(glm::vec2 pos);
	glm::vec2 getPosition();

	bool Intersect(sf::CircleShape* circle) override;
	bool Intersect(sf::FloatRect* rect) override;

	void Render(sf::RenderWindow* window) override;
	void DebugDraw(sf::RenderWindow* window) override;

	void Move(sf::Time delta) override;
	glm::vec2 Seek(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Flee(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Arrive(const glm::vec2 currentVelocity, glm::vec2 currentTarget);

	glm::vec2 truncate(glm::vec2 totrunc, float);
	void MarkPosition();

private:
	glm::vec2 position;
	glm::vec2 velocity;
	RenderObject* renderObject;
	sf::CircleShape* boundingCircle;

	glm::vec2 target;
	float maxSpeed;
	float steeringForce;
	float arrivalRadius;

	float timeSincePoint;
	vector<sf::CircleShape> trajectory;
};
