#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Renderable.h"
#include "Moving.h"
#include "SFML/Graphics.hpp"
#include "Path.h"

class Formation : public Renderable, public Moving
{
public:
	Formation();
	~Formation();
	
	int registerSoldier();
	glm::vec2 GetOffsetForIndex(int index);
	void SetPath(Path* newpath);
	
	void Render(sf::RenderWindow* window) override;
	void DebugDraw(sf::RenderWindow* window) override;

	void Move(sf::Time delta) override;
	void SetRotation(float rot);
	void SetPosition(glm::vec2 pos);

	glm::vec2 Seek(const glm::vec2 currentVelocity, glm::vec2 currentTarget);
	glm::vec2 truncate(glm::vec2 totrunc, float) const;

protected:
	std::vector<sf::CircleShape*> offsets;
	int currIndex;

	glm::vec2 position;
	glm::vec2 velocity;
	float maxSpeed = 120.0f;
	float steeringForce = 6.0f;
	glm::vec2 target;

	glm::vec2 leaderPos;
	float orientation;

	Path* pathtofollow;
	int currentWaypoint = 0;
	float tolerance = 10.0f;
};
