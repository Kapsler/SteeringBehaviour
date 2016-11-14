#include "WedgeFormation.h"

WedgeFormation::WedgeFormation()
{
	sf::CircleShape* leadertmp = new sf::CircleShape;
	leadertmp->setPosition(0.0f, 0.0f);
	leadertmp->setRadius(10.0f);
	leadertmp->setOrigin(leadertmp->getPosition().x + leadertmp->getGlobalBounds().width / 2, leadertmp->getPosition().y + leadertmp->getGlobalBounds().height / 2);
	offsets.push_back(leadertmp);

	sf::CircleShape* tmp = new sf::CircleShape;
	tmp->setPosition(-50.0f, 50.0f);
	tmp->setRadius(10.0f);
	tmp->setOrigin(leadertmp->getPosition().x + leadertmp->getGlobalBounds().width / 2, leadertmp->getPosition().y + leadertmp->getGlobalBounds().height / 2);
	offsets.push_back(tmp);

	tmp = new sf::CircleShape;
	tmp->setPosition(50.0f, 50.0f);
	tmp->setRadius(10.0f);
	tmp->setOrigin(leadertmp->getPosition().x + leadertmp->getLocalBounds().width / 2, leadertmp->getPosition().y + leadertmp->getLocalBounds().height / 2);
	offsets.push_back(tmp);

	tmp = new sf::CircleShape;
	tmp->setPosition(100.0f, 100.0f);
	tmp->setRadius(10.0f);
	tmp->setOrigin(leadertmp->getPosition().x + leadertmp->getLocalBounds().width / 2, leadertmp->getPosition().y + leadertmp->getLocalBounds().height / 2);
	offsets.push_back(tmp);
}

WedgeFormation::~WedgeFormation()
{
}
