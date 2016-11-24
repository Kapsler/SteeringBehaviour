#include "Agent.h"

Agent::Agent(string fileName)
{
	//General Attributes
	renderObject = new RenderObject(fileName);
	renderObject->sprite.setOrigin(renderObject->sprite.getLocalBounds().width / 2.5f, renderObject->sprite.getLocalBounds().height / 3);
	renderObject->sprite.scale(0.15f, 0.15f);

	//Moving related
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	maxSpeed = 180.0f;
	maxSteeringForce = 6.0f;
	arrivalRadius = 50.0f; 
	separationTolerance = 25.0f; 
	lookahead = 150.0f;

	//Feelers
	whiskerMiddle.origin = position;
	whiskerMiddle.direction = normalize(velocity);
	whiskerMiddle.length = 30.0f;
	whiskerMiddle.tag = 'm';
	feelers.push_back(&whiskerMiddle);

	whiskerLeft.origin = position;
	whiskerLeft.direction = normalize(glm::rotate(velocity, -20.0f));
	whiskerLeft.length = 30.0f;
	whiskerLeft.tag = 'l';
	feelers.push_back(&whiskerLeft);

	whiskerRight.origin = position;
	whiskerRight.direction = normalize(glm::rotate(velocity, 20.0f));
	whiskerRight.length = 30.0f;
	whiskerRight.tag = 'r';
	feelers.push_back(&whiskerRight);

	//trajectory
	timeSincePoint = 0.0f;

	targettype = 1;
	ToggleTargetType();
}

Agent::Agent(const Agent&)
{
}

Agent::~Agent()
{
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
	renderObject->SetPosition(pos);

}

void Agent::setFormation(Formation* form)
{
	formation = form;
	index = form->registerSoldier();	
}

glm::vec2 Agent::getPosition() const
{
	return position;
}

void Agent::setRotation(float rot)
{
	orientation = rot;
	renderObject->SetRotation(rot);
}

float Agent::GetRotation() const
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
	//Velocity direction
	sf::RectangleShape velocityRectangle;
	velocityRectangle.setSize(sf::Vector2f(glm::length(velocity), 3.0f));
	velocityRectangle.setOrigin(velocityRectangle.getOrigin().x, velocityRectangle.getGlobalBounds().height / 2);
	velocityRectangle.setPosition(position.x, position.y);
	velocityRectangle.setRotation(orientation);
	velocityRectangle.setFillColor(sf::Color::Green);
	window->draw(velocityRectangle);

	sf::Vertex* line = new sf::Vertex[2];
	sf::Vector2f tmp1, tmp2;
	//Draw whiskers
	for(const auto& whisk : feelers)
	{
		tmp1 = sf::Vector2f(whisk->origin.x, whisk->origin.y);
		line[0] = sf::Vertex(tmp1, sf::Color::Magenta);
		tmp2 = sf::Vector2f(whisk->origin.x + whisk->direction.x * whisk->length, whisk->origin.y + whisk->direction.y * whisk->length);
		line[1] = sf::Vertex(tmp2, sf::Color::Magenta);
		window->draw(line, 2, sf::LineStrip);
	}

	for(const auto& l : linestodraw)
	{
		tmp1 = sf::Vector2f(l.start.x, l.start.y);
		line[0] = sf::Vertex(tmp1, sf::Color::Red);
		tmp2 = sf::Vector2f(l.end.x, l.end.y);
		line[1] = sf::Vertex(tmp2, sf::Color::Red);
		window->draw(line, 2, sf::LineStrip);
	}
	delete[] line;

	linestodraw.clear();

}

void Agent::Move(sf::Time deltaTime)
{
	timeSincePoint += deltaTime.asSeconds();
	if(timeSincePoint > 0.25f)
	{
		MarkPosition();
		timeSincePoint = 0.0f;
	}

	glm::vec2 blendedSteering, moveSteering, separationSteering, avoidanceSteering, evadeSteering;
	
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
	case 4:
		moveSteering = Persue(velocity, target, lasttarget);
		break;
	case 5:
		moveSteering = Evade(velocity, target, lasttarget);
		break;
	default:
		break;
	}
	lasttarget = target;

	//Separation
	separationSteering = Separate(velocity);

	//Avoidance
	avoidanceSteering = AvoidObstacles(velocity);

	//Evading
	evadeSteering = AvoidEnemies(velocity);

	//Blending
	blendedSteering = moveSteering * 1.0f;
	blendedSteering += separationSteering * 4.0f;
	blendedSteering += avoidanceSteering * 5.0f;
	blendedSteering += evadeSteering * 1.2f;

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

glm::vec2 Agent::Seek(const glm::vec2& currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = glm::normalize(currentTarget - position) * maxSpeed;
	glm::vec2 newSteering = desiredVelocity - currentVelocity;

	newSteering = truncate(newSteering, maxSteeringForce);

	return newSteering;
}

glm::vec2 Agent::Flee(const glm::vec2& currentVelocity, glm::vec2 currentTarget)
{
	glm::vec2 desiredVelocity = glm::normalize(position - currentTarget) * maxSpeed;
	glm::vec2 newSteering = desiredVelocity - currentVelocity;

	newSteering = truncate(newSteering, maxSteeringForce);

	return newSteering;
}

glm::vec2 Agent::Persue(const glm::vec2& currentVelocity, glm::vec2 currentTarget, glm::vec2 lastpos)
{
	float T = glm::length(currentTarget - position) / maxSpeed;
	glm::vec2 futureTarget = currentTarget + normalize(currentTarget - lastpos) * T;
	
	return Seek(currentVelocity, futureTarget);
}

glm::vec2 Agent::Evade(const glm::vec2& currentVelocity, glm::vec2 currentTarget, glm::vec2 lastpos)
{
	float T = glm::length(currentTarget - position) / maxSpeed;
	glm::vec2 futureTarget = currentTarget + normalize(currentTarget - lastpos) * T;

	return Flee(currentVelocity, futureTarget);
}

glm::vec2 Agent::EvadeVel(const glm::vec2& currentVelocity, glm::vec2 currentTarget, glm::vec2 targetvelocity)
{
	float T = glm::length(currentTarget - position) / maxSpeed;
	glm::vec2 futureTarget = currentTarget + normalize(targetvelocity) * T;

	return Flee(currentVelocity, futureTarget);
}

glm::vec2 Agent::Arrive(const glm::vec2& currentVelocity, glm::vec2 currentTarget)
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

glm::vec2 Agent::Separate(const glm::vec2& currentVelocity)
{
	glm::vec2 separation = glm::vec2(0.0f, 0.0f);
	int count = 0;
	float distance;

	if(actors != nullptr)
	{
		for(auto* a : *actors)
		{
			distance = glm::distance(position, a->getPosition());
			if(distance > 0 && distance < separationTolerance)
			{
				separation = Flee(currentVelocity, a->getPosition());
			}
		}
	}
	

	if(count > 0)
	{
		separation /= count;
	}

	return separation;
}

glm::vec2 Agent::AvoidObstacles(const glm::vec2& currentVelocity)
{
	glm::vec2 avoidance = glm::vec2(0.0f, 0.0f);
	int count = 0;


	glm::vec2 A, B, C, D;

	for(const auto& whisk : feelers)
	{
		A = whisk->origin;
		B = whisk->origin + whisk->direction * whisk->length;

		if (obstacles != nullptr)
		{
			for (const auto& o : *obstacles)
			{

				for (auto i = 0; i < o.getPointCount(); i++)
				{
					float u = 0;

					C.x = o.getTransform().transformPoint(o.getPoint(i)).x;
					C.y = o.getTransform().transformPoint(o.getPoint(i)).y;

					D.x = o.getTransform().transformPoint(o.getPoint((i + 1) % o.getPointCount())).x;
					D.y = o.getTransform().transformPoint(o.getPoint((i + 1) % o.getPointCount())).y;

					if (LineIntersection(A, B, C, D, u))
					{
						//Intersection Occurs!

						if (whisk->tag == 'm')
						{
							//Middle
							glm::vec2 PoI = C + ((D - C) * u);
							glm::vec2 normal((D - C).y, -(D - C).x);

							avoidance += Seek(currentVelocity, PoI + normalize(normal) * whisk->length);

							count++;
						}
						else if (whisk->tag == 'l')
						{
							//Left	
							avoidance += Seek(currentVelocity, whiskerRight.origin + whiskerRight.direction * whiskerRight.length);

							count++;
						}
						else if (whisk->tag == 'r')
						{
							//Right
							avoidance += Seek(currentVelocity, whiskerLeft.origin + whiskerLeft.direction * whiskerLeft.length);

							count++;
						}

					}

				}
			}
		}
		
	}

	
	if (count > 0)
	{
		avoidance /= count;
	}

	return avoidance;
}

glm::vec2 Agent::AvoidEnemies(const glm::vec2& currentVelocity)
{

	glm::vec2 avoidance = glm::vec2(0.0f, 0.0f);
	int count = 0;

	glm::vec2 A, B, C, D;

	A = getPosition();
	B = getPosition() + glm::normalize(getVelocity()) * lookahead;

	if (enemies != nullptr)
	{
		for(const auto* e : *enemies)
		{
			float u = 0;

			C = e->getPosition();
			D = e->getPosition() + glm::normalize(e->getVelocity()) * lookahead;

			//if(LineIntersection(A, B, C, D, u))
			if(glm::length(C - A) < lookahead/2)
			{
				avoidance += EvadeVel(currentVelocity, C, e->getVelocity());
				count++;
			}
			
		}
	}
	
	if (count > 0)
	{
		avoidance /= count;
	}

	return avoidance;
}

glm::vec2 Agent::getVelocity() const
{
	return velocity;
}

void Agent::SetSeparationActors(vector<Agent*> *others)
{
	actors = others;
}

void Agent::SetObstacles(vector<sf::RectangleShape> *others)
{
	obstacles = others;
}

void Agent::SetEnemys(vector<Agent*>* others)
{
	enemies = others;
}

bool Agent::LineIntersection(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 D, float& u)
{
	glm::vec2 p = A;
	glm::vec2 q = C;
	glm::vec2 r = B - A;
	glm::vec2 s = D - C;
	glm::vec2 qminp = q - p;
	
	float rxs = crossVec2(r, s);
	float qminpxr = crossVec2(qminp, r);

	if(rxs == 0.0f && qminpxr == 0.0f)
	{
		//Collinear

		//TODO Build overlap check
		/*float rdotr = dot(r, r);

		float t0 = glm::dot(qminp, r) / rdotr;
		float t1 = t0 + dot(s, r) / rdotr;*/
		
		return false;
	}

	if(rxs == 0)
	{
		//Parallel
		return false;
	}

	float qminpxs = crossVec2(qminp, s);
	float t = qminpxs / rxs;
	u = qminpxr / rxs;

	return ((t >= 0.0f) && (t <= 1.0f) && (u >= 0.0f) && (u <= 1.0f));
}

float Agent::crossVec2(const glm::vec2& a, const glm::vec2& b)
{
	return a.x * b.y - a.y * b.x;
}

void Agent::RepositionWhiskers()
{
	whiskerMiddle.origin = position;
	whiskerMiddle.direction = normalize(velocity);

	whiskerLeft.origin = position;
	whiskerLeft.direction = rotate(normalize(velocity), -0.5f);

	whiskerRight.origin = position;
	whiskerRight.direction = rotate(normalize(velocity), 0.5f);
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
	if(trajectory.size() > 200)
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
	if (targettype > 5) targettype = 1;

	switch (targettype)
	{
	case 1:
		cout << "Seek" << endl;
		break;
	case 2:
		cout << "Arrive" << endl;
		break;
	case 3:
		cout << "Flee" << endl;
		break;
	case 4:
		cout << "Pursue" << endl;
		break;
	case 5:
		cout << "Evade" << endl;
		break;
	default:
		break;
	}
}
