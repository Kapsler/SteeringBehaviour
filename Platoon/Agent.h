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
	glm::vec2 getPosition() const;
	void setRotation(float rot);
	float GetRotation() const;

	void Render(sf::RenderWindow* window) override;
	void DebugDraw(sf::RenderWindow* window) override;

	void Move(sf::Time delta) override;
	glm::vec2 Seek(const glm::vec2& currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Flee(const glm::vec2& currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Persue(const glm::vec2& currentVelocity, glm::vec2 currentTarget, glm::vec2 lastpos);
	glm::vec2 Evade(const glm::vec2& currentVelocity, glm::vec2 currentTarget, glm::vec2 lastpos);
	glm::vec2 EvadeVel(const glm::vec2& currentVelocity, glm::vec2 currentTarget, glm::vec2 targetvelocity);
	glm::vec2 Arrive(const glm::vec2& currentVelocity, glm::vec2 currentTarget);
	glm::vec2 Separate(const glm::vec2& currentVelocity);
	glm::vec2 AvoidObstacles(const glm::vec2& currentVelocity);
	glm::vec2 AvoidEnemies(const glm::vec2& currentVelocity);

	glm::vec2 getVelocity() const;

	void SetSeparationActors(vector<Agent*> *others);
	void SetObstacles(vector<sf::RectangleShape> *others);
	void SetEnemys(vector<Agent*> *others);

	bool LineIntersection(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D, float& u);
	static float crossVec2(const glm::vec2& a, const glm::vec2& b);

	void RepositionWhiskers();

	glm::vec2 truncate(glm::vec2 totrunc, float);
	void MarkPosition();
	void ToggleTargetType();

private:
	glm::vec2 position;
	glm::vec2 velocity;
	float orientation;
	RenderObject* renderObject;

	glm::vec2 target;
	glm::vec2 lasttarget;
	float lookahead;
	float maxSpeed;
	float maxSteeringForce;
	float arrivalRadius;
	float separationTolerance;
	Formation* formation;
	std::vector<glm::vec2> path;
	vector<Agent*> *actors = nullptr;
	vector<Agent*> *enemies = nullptr;

	struct feeler
	{
		glm::vec2 origin;
		glm::vec2 direction;
		float length;
		char tag;
	};

	feeler whiskerMiddle;
	feeler whiskerLeft;
	feeler whiskerRight;
	vector<feeler*> feelers;
	vector<sf::RectangleShape> *obstacles = nullptr;

	float timeSincePoint;
	vector<sf::CircleShape> trajectory;
	int targettype;
	int index;

	struct line
	{
		glm::vec2 start;
		glm::vec2 end;
	};

	vector<line> linestodraw;

};
