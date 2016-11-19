#pragma once
#include "RenderObject.h"
#include "Collidable.h"


class Wall : public RenderObject, public Collidable
{
public:
	Wall(glm::vec2 pos);
	~Wall();

	

};
