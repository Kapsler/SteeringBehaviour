#pragma once
#include "RenderObject.h"
#include "Collidable.h"
#include "Moving.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Formation.h"

class Agent : public Renderable, public Collidable, public Moving
{
public:
	Agent(string fileName);
	Agent(const Agent&);
	~Agent();

	void setPosition(glm::vec2 pos);
	void setFormation(Formation* form);
	glm::vec2 getPosition();
	void setRotation(float rot);
	float GetRotation();

	void Render(sf::RenderWindow* window) override;
	void DebugDraw(sf::RenderWindow* window) override;

	void Move(sf::Time delta) override;
	glm::vec2 Seek(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Flee(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Arrive(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Separate(const glm::vec2 currentVelocity);
	glm::vec2 AvoidObstacles(const glm::vec2 currentVelocity);

	void SetSeparationActors(vector<Agent*> *others);
	void SetObstacles(vector<sf::FloatRect> *others);

	void RepositionWhiskers();

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
	vector<Agent*> *actors;

	struct feeler
	{
		glm::vec2 origin;
		glm::vec2 direction;
		float length;
	};

	sf::RectangleShape middleWhisker;
	sf::RectangleShape leftWhisker;
	sf::RectangleShape rightWhisker;

	feeler whiskerMiddle;
	feeler whiskerLeft;
	feeler whiskerRight;
	vector<sf::FloatRect> *obstacles;

	float timeSincePoint;
	vector<sf::CircleShape> trajectory;
	int targettype;
	int index;

};
