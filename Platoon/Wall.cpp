#include "Wall.h"

Wall::Wall(glm::vec2 pos): RenderObject("./Assets/wall.jpg", pos)
{
	sprite.scale(0.1f, 0.02f);
}

Wall::~Wall()
{
}
