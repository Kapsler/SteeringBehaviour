#include "Agent.h"

Agent::Agent(string fileName)
{
	//General Attributes
	renderObject = new RenderObject(fileName);
	renderObject->sprite.setOrigin(renderObject->sprite.getLocalBounds().width / 2.5f, renderObject->sprite.getLocalBounds().height / 3);
	renderObject->sprite.scale(0.2f, 0.2f);

	//BoundingCirlce
	float biggerside = renderObject->sprite.getGlobalBounds().width;
	if (renderObject->sprite.getGlobalBounds().height > biggerside) biggerside = renderObject->sprite.getGlobalBounds().height;
	boundingCircle = new sf::CircleShape(biggerside / 2);
	boundingCircle->setPosition(sf::Vector2f(renderObject->sprite.getPosition().x - renderObject->sprite.getGlobalBounds().width / 2, renderObject->sprite.getPosition().y - renderObject->sprite.getGlobalBounds().height / 2));
	//Moving related
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	maxSpeed = 180.0f;
	maxSteeringForce = 6.0f;
	arrivalRadius = 50.0f; 
	separationTolerance = 30.0f;

	//Feelers
	//whiskerMiddle.origin = position;
	//whiskerMiddle.direction = normalize(velocity);
	//whiskerMiddle.length = 30.0f;

	//whiskerLeft.origin = position;
	//whiskerLeft.direction = normalize(glm::rotate(velocity, -20.0f));
	//whiskerLeft.length = 20.0f;

	//whiskerRight.origin = position;
	//whiskerRight.direction = normalize(glm::rotate(velocity, 20.0f));
	//whiskerRight.length = 20.0f;
	
	middleWhisker.setSize(sf::Vector2f(50.0f, 1.0f));
	leftWhisker.setSize(sf::Vector2f(30.0f, 1.0f));
	rightWhisker.setSize(sf::Vector2f(30.0f, 1.0f));

	//trajectory
	timeSincePoint = 0.0f;

	//Hardcoded Target
	target.x = 800.0f;
	target.y = 800.0f;
	targettype = 1;
	ToggleTargetType();
	//Target end
}

Agent::Agent(const Agent&)
{
}

Agent::~Agent()
{
	delete boundingCircle;
	boundingCircle = nullptr;

	delete renderObject;
	renderObject = nullptr;
}

void Agent::setPosition(glm::vec2 pos)
{
	//Bind in screen
	if (pos.x < 0) pos.x = 0;
	if (pos.y < 0) pos.y = 0;
	if (pos.x > 1000) pos.x = 1000;
	if (pos.y > 1000) pos.y = 1000;

	position = pos;
	renderObject->setPosition(pos);
	boundingCircle->setPosition(sf::Vector2f(position.x - renderObject->sprite.getGlobalBounds().width / 2, position.y - renderObject->sprite.getGlobalBounds().height / 2));

}

void Agent::setFormation(Formation* form)
{
	formation = form;
	index = form->registerSoldier();	
}

glm::vec2 Agent::getPosition()
{
	return position;
}

void Agent::setRotation(float rot)
{
	renderObject->setRotation(rot);
	//boundingCircle->setRotation(rot);
}

float Agent::GetRotation()
{
	return renderObject->sprite.getRotation();
}

void Agent::Render(sf::RenderWindow* window)
{
	renderObject->Render(window);
	for(auto i : trajectory)
	{
		window->draw(i);
	}
}

void Agent::DebugDraw(sf::RenderWindow* window)
{
	//Debug Fill Color
	boundingCircle->setFillColor(sf::Color(180, 40, 40, 120));
	window->draw(*boundingCircle);
	boundingCircle->setFillColor(sf::Color::Transparent);

	//Target follow mouse
	sf::Vector2f mouse = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	target.x = mouse.x;
	target.y = mouse.y;
	//End following

	sf::CircleShape targetshape;
	targetshape.setRadius(2);
	targetshape.setPosition(target.x - targetshape.getRadius(), target.y - targetshape.getRadius());

	window->draw(targetshape);

	//sf::Vertex* line = new sf::Vertex[2];
	//sf::Vector2f tmp1, tmp2;
	////Draw whiskers
	//tmp1 = sf::Vector2f(whiskerMiddle.origin.x, whiskerMiddle.origin.y);
	//line[0] = sf::Vertex(tmp1, sf::Color::Magenta);
	//tmp2 = sf::Vector2f(whiskerMiddle.origin.x + whiskerMiddle.direction.x * whiskerMiddle.length, whiskerMiddle.origin.y + whiskerMiddle.direction.y * whiskerMiddle.length);
	//line[1] = sf::Vertex(tmp2, sf::Color::Magenta);
	//window->draw(line, 2, sf::LineStrip);

	//tmp1 = sf::Vector2f(whiskerLeft.origin.x, whiskerLeft.origin.y);
	//line[0] = sf::Vertex(tmp1, sf::Color::Magenta);
	//tmp2 = sf::Vector2f(whiskerLeft.origin.x + whiskerLeft.direction.x * whiskerLeft.length, whiskerLeft.origin.y + whiskerLeft.direction.y * whiskerLeft.length);
	//line[1] = sf::Vertex(tmp2, sf::Color::Magenta);
	//window->draw(line, 2, sf::LineStrip);

	//tmp1 = sf::Vector2f(whiskerRight.origin.x, whiskerRight.origin.y);
	//line[0] = sf::Vertex(tmp1, sf::Color::Magenta);
	//tmp2 = sf::Vector2f(whiskerRight.origin.x + whiskerRight.direction.x * whiskerRight.length, whiskerRight.origin.y + whiskerRight.direction.y * whiskerRight.length);
	//line[1] = sf::Vertex(tmp2, sf::Color::Magenta);
	//window->draw(line, 2, sf::LineStrip);

	//delete[] line;

	middleWhisker.setFillColor(sf::Color::Magenta);
	window->draw(middleWhisker);
	leftWhisker.setFillColor(sf::Color::Magenta);
	window->draw(leftWhisker);
	rightWhisker.setFillColor(sf::Color::Magenta);
	window->draw(rightWhisker);

	for(auto i : intersections)
	{
		sf::RectangleShape rec;
		rec.setSize(sf::Vector2f(i.rect.width, i.rect.height));
		rec.setPosition(i.rect.left, i.rect.top);
		rec.setRotation(i.rot);
		rec.setFillColor(sf::Color::Cyan);
		window->draw(rec);
	}


}

void Agent::Move(sf::Time deltaTime)
{
	timeSincePoint += deltaTime.asSeconds();
	if(timeSincePoint > 0.25f)
	{
		MarkPosition();
		timeSincePoint = 0.0f;
	}

	glm::vec2 blendedSteering, moveSteering, separationSteering, avoidanceSteering;
	
	target = formation->GetPositionForIndex(index);

	//What to do
	switch(targettype)
	{
	case 1:
		moveSteering = Seek(velocity, target);
		break;
	case 2:
		moveSteering = Arrive(velocity, target);
		break;
	case 3:
		moveSteering = Flee(velocity, target);
		break;
	default:
		break;
	}

	//Separation
	separationSteering = Separate(velocity);

	//Avoidance
	avoidanceSteering = AvoidObstacles(velocity);

	//Blending
	blendedSteering = moveSteering * 1.0f;
	blendedSteering += separationSteering * 3.0f;
	blendedSteering += avoidanceSteering * 5.0f;

	truncate(blendedSteering, maxSteeringForce);

	velocity = velocity + blendedSteering * deltaTime.asSeconds() * 100.0f;
	velocity = truncate(velocity, maxSpeed) ;
	if ((velocity.x < -0.00001f || velocity.x > 0.00001f) && (velocity.y < -0.00001f || velocity.y > 0.00001f))
	{
		setPosition(position + velocity * deltaTime.asSeconds());
		setRotation(atan2(normalize(velocity).y, normalize(velocity).x) * 180.0f / 3.1415926f); 
		RepositionWhiskers();
	}
}

glm::vec2 Agent::Seek(const glm::vec2 currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = glm::normalize(currentTarget - position) * maxSpeed;
	glm::vec2 newSteering = desiredVelocity - currentVelocity;

	newSteering = truncate(newSteering, maxSteeringForce);

	return newSteering;
}

glm::vec2 Agent::Flee(const glm::vec2 currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = glm::normalize(position - currentTarget) * maxSpeed;
	glm::vec2 newSteering = desiredVelocity - currentVelocity;

	newSteering = truncate(newSteering, maxSteeringForce);

	return newSteering;
}

glm::vec2 Agent::Arrive(const glm::vec2 currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = currentTarget - position;
	float distance = glm::distance(currentTarget, position);

	if(distance < arrivalRadius)
	{
		desiredVelocity = glm::normalize(desiredVelocity) * maxSpeed * (distance / arrivalRadius);
	} else
	{
		desiredVelocity = glm::normalize(desiredVelocity) * maxSpeed;
	}

	glm::vec2 newSteering;
	newSteering = desiredVelocity - currentVelocity;
	
	newSteering = truncate(newSteering, maxSteeringForce);

	return newSteering;
}

glm::vec2 Agent::Separate(const glm::vec2 currentVelocity)
{
	glm::vec2 separation = glm::vec2(0.0f, 0.0f);
	int count = 0;
	float distance;

	for(auto* a : *actors)
	{
		distance = glm::distance(position, a->getPosition());
		if(distance > 0 && distance < separationTolerance)
		{
			//cout << "GET AWAY FROM ME!" << endl;
			separation = Flee(currentVelocity, a->getPosition());
		}
	}

	if(count > 0)
	{
		separation /= count;
	}

	return separation;
}

glm::vec2 Agent::AvoidObstacles(const glm::vec2 currentVelocity)
{
	glm::vec2 avoidance = glm::vec2(0.0f, 0.0f);
	int count = 0;

	sf::Vector2f middlePoint, leftPoint, rightPoint;

	//middlePoint.x = (whiskerMiddle.origin.x + whiskerMiddle.direction.x * whiskerMiddle.length);
	//middlePoint.y = (whiskerMiddle.origin.y + whiskerMiddle.direction.y * whiskerMiddle.length);
	//leftPoint.x = (whiskerMiddle.origin.x + whiskerMiddle.direction.x * whiskerMiddle.length);
	//leftPoint.y = (whiskerMiddle.origin.y + whiskerMiddle.direction.y * whiskerMiddle.length);
	//rightPoint.x = (whiskerMiddle.origin.x + whiskerMiddle.direction.x * whiskerMiddle.length);
	//rightPoint.y = (whiskerMiddle.origin.y + whiskerMiddle.direction.y * whiskerMiddle.length);

	intersections.clear();

	intersection inter;

	for(auto o : *obstacles)
	{
		////Collision Middle
		//if (o.contains(middlePoint))
		//{
		//	cout << "Collision" << endl;
		//	avoidance += Seek(currentVelocity, whiskerLeft.origin + whiskerLeft.direction * whiskerLeft.length);

		//	//TODO LineLine Collision
		//	//FInd intersection of line, apply normal vector
		//}

		////Collision Left
		//if(o.contains(leftPoint))
		//{
		//	cout << "Collision" << endl;
		//	avoidance += Seek(currentVelocity, whiskerRight.origin + whiskerRight.direction * whiskerRight.length);

		//	//TODO LineLine Collision
		//	//FInd intersection of line, apply normal vector
		//}

		////Collision Right
		//if (o.contains(rightPoint))
		//{
		//	cout << "Collision" << endl;
		//	avoidance += Seek(currentVelocity, whiskerLeft.origin + whiskerLeft.direction * whiskerLeft.length);

		//	//TODO LineLine Collision
		//	//FInd intersection of line, apply normal vector
		//}

		if(o.intersects(middleWhisker.getGlobalBounds(), inter.rect))
		{
			sf::Vector2f point = leftWhisker.getPoint(1);
			avoidance += Seek(currentVelocity, glm::vec2(leftWhisker.getTransform().transformPoint(point).x, leftWhisker.getTransform().transformPoint(point).y));
			count++;
			inter.rot = middleWhisker.getRotation();
			intersections.push_back(inter);
		}

		if(o.intersects(leftWhisker.getGlobalBounds(), inter.rect))
		{
			sf::Vector2f point = rightWhisker.getPoint(1);
			avoidance += Seek(currentVelocity, glm::vec2(rightWhisker.getTransform().transformPoint(point).x, rightWhisker.getTransform().transformPoint(point).y));
			count++;
			inter.rot = leftWhisker.getRotation();
			intersections.push_back(inter);
		}

		if(o.intersects(rightWhisker.getGlobalBounds(), inter.rect))
		{
			sf::Vector2f point = leftWhisker.getPoint(1);
			avoidance += Seek(currentVelocity, glm::vec2(leftWhisker.getTransform().transformPoint(point).x, leftWhisker.getTransform().transformPoint(point).y));
			count++;
			inter.rot = rightWhisker.getRotation();
			intersections.push_back(inter);
		}
	}
	
	if (count > 0)
	{
		avoidance /= count;
	}

	return avoidance;
}

void Agent::SetSeparationActors(vector<Agent*> *others)
{
	actors = others;
}

void Agent::SetObstacles(vector<sf::FloatRect> *others)
{
	obstacles = others;
}

void Agent::RepositionWhiskers()
{
	whiskerMiddle.origin = position;
	whiskerMiddle.direction = normalize(velocity);

	whiskerLeft.origin = position;
	whiskerLeft.direction = rotate(normalize(velocity), -0.5f);

	whiskerRight.origin = position;
	whiskerRight.direction = rotate(normalize(velocity), 0.5f);

	middleWhisker.setPosition(position.x, position.y);
	middleWhisker.setRotation(atan2(normalize(velocity).y, normalize(velocity).x) * 180.0f / 3.1415926f);

	leftWhisker.setPosition(position.x, position.y);
	leftWhisker.setRotation(atan2(normalize(velocity).y, normalize(velocity).x) * 180.0f / 3.1415926f);
	leftWhisker.rotate(-45);

	rightWhisker.setPosition(position.x, position.y);
	rightWhisker.setRotation(atan2(normalize(velocity).y, normalize(velocity).x) * 180.0f / 3.1415926f);
	rightWhisker.rotate(45);
}

glm::vec2 Agent::truncate(glm::vec2 totrunc, float max)
{
	float i = max / glm::length(totrunc);
	if(i > 1.0f)
	{
		i = 1.0f;
	}

	return totrunc * i;
}

void Agent::MarkPosition()
{
	if(trajectory.size() > 50)
	{
		trajectory.erase(trajectory.begin());
	}
	
	sf::CircleShape newpoint;
	newpoint.setPosition(position.x, position.y);
	newpoint.setRadius(5.0f);
	newpoint.setFillColor(sf::Color(180, 40, 40, 120));

	trajectory.push_back(sf::CircleShape(newpoint));
}

void Agent::ToggleTargetType()
{
	targettype++;
	if (targettype > 3) targettype = 1;

	switch (targettype)
	{
	case 1:
		cout << "Where is that bastard..." << endl;
		break;
	case 2:
		cout << "There he is!" << endl;
		break;
	case 3:
		cout << "OMG! RUN FOR YOUR LIFES!!" << endl;
		break;
	default:
		break;
	}
}
