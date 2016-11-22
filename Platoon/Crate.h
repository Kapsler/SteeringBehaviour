#pragma once
#include "RenderObject.h"


class Crate : public RenderObject
{
public:
	Crate(glm::vec2 pos);
	~Crate();

	void DebugDraw(sf::RenderWindow* window) override;
};
