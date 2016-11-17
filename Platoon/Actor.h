#pragma once
#include "RenderObject.h"
#include "Collidable.h"
#include "Moving.h"
#include <glm/glm.hpp>
#include "Formation.h"

class Actor : public Renderable, public Collidable, public Moving
{
public:
	Actor(string fileName);
	Actor(const Actor&);
	~Actor();

	void setPosition(glm::vec2 pos);
	void setFormation(Formation* form);
	glm::vec2 getPosition();
	void setRotation(float rot);
	float GetRotation();

	bool Intersect(sf::CircleShape* circle) override;
	bool Intersect(sf::FloatRect* rect) override;

	void Render(sf::RenderWindow* window) override;
	void DebugDraw(sf::RenderWindow* window) override;

	void Move(sf::Time delta) override;
	glm::vec2 Seek(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Flee(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Arrive(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Separate(const glm::vec2 currentVelocity);

	void SetSeparationActors(vector<Actor*> others);

	glm::vec2 truncate(glm::vec2 totrunc, float);
	void MarkPosition();
	void ToggleTargetType();

private:
	glm::vec2 position;
	glm::vec2 velocity;
	RenderObject* renderObject;
	sf::CircleShape* boundingCircle;

	glm::vec2 target;
	float maxSpeed;
	float maxSteeringForce;
	float arrivalRadius;
	float separationTolerance;
	Formation* formation;
	std::vector<glm::vec2> path;
	vector<Actor*> actors;

	float timeSincePoint;
	vector<sf::CircleShape> trajectory;
	int targettype;
	int index;

};
