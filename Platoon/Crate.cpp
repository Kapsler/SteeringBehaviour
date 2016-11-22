#include "Crate.h"

Crate::Crate(glm::vec2 pos): RenderObject("./Assets/crate.jpg", pos)
{
	Scale(0.2f, 0.2f);
}

Crate::~Crate()
{
}

void Crate::DebugDraw(sf::RenderWindow* window)
{
}
