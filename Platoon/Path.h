#pragma once
#include "Moving.h"
#include "Renderable.h"
#include "../packages/glm.0.9.7.1/build/native/include/glm/detail/type_vec2.hpp"

class Path : public Renderable
{
public:
	Path();
	~Path();

	void Render(sf::RenderWindow* window) override;
	void DebugDraw(sf::RenderWindow* window) override;

	void AddPoint(glm::vec2 newpoint);
	glm::vec2 GetPoint(int index);


private:
	std::vector<glm::vec2> waypoints;

};
