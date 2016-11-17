#include "WedgeFormation.h"

WedgeFormation::WedgeFormation()
{
	sf::CircleShape* leadertmp = new sf::CircleShape;
	leadertmp->setPosition(0.0f, 0.0f);
	leadertmp->setRadius(10.0f);
	leadertmp->setOrigin(leadertmp->getPosition().x + leadertmp->getRadius(), leadertmp->getPosition().y + leadertmp->getRadius());
	offsets.push_back(leadertmp);

	sf::CircleShape* tmp = new sf::CircleShape;
	tmp->setPosition(-30.0f, 30.0f);
	tmp->setRadius(10.0f);
	tmp->setOrigin(leadertmp->getPosition().x + leadertmp->getRadius(), leadertmp->getPosition().y + leadertmp->getRadius());
	offsets.push_back(tmp);

	tmp = new sf::CircleShape;
	tmp->setPosition(30.0f, 30.0f);
	tmp->setRadius(10.0f);
	tmp->setOrigin(leadertmp->getPosition().x + leadertmp->getRadius(), leadertmp->getPosition().y + leadertmp->getRadius());
	offsets.push_back(tmp);

	tmp = new sf::CircleShape;
	tmp->setPosition(60.0f, 60.0f);
	tmp->setRadius(10.0f);
	tmp->setOrigin(leadertmp->getPosition().x + leadertmp->getRadius(), leadertmp->getPosition().y + leadertmp->getRadius());
	offsets.push_back(tmp);
}

WedgeFormation::~WedgeFormation()
{
}
