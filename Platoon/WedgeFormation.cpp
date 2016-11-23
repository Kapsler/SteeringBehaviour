#include "WedgeFormation.h"
#include <glm/gtc/constants.inl>

WedgeFormation::WedgeFormation()
{
	AddSlot(glm::quarter_pi<float>() * 3, 30.0f);

	AddSlot(glm::quarter_pi<float>() * 3, 60.0f);

	AddSlot(-glm::quarter_pi<float>() * 3, 30.0f);
}

WedgeFormation::~WedgeFormation()
{
}
