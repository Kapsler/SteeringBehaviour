#include "Wall.h"

Wall::Wall(glm::vec2 pos): RenderObject("./Assets/wall.jpg", pos)
{
	Scale(0.1f, 0.02f);
}

Wall::~Wall()
{
}

void Wall::DebugDraw(sf::RenderWindow* window)
{

}
