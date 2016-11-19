#include <SFML/Graphics.hpp>
#include "RenderObject.h"
#include "Agent.h"
#include <glm/glm.hpp>
#include "WedgeFormation.h"
#include "Path.h"
#include "Wall.h"

std::vector<Renderable*> renderObjects;
std::vector<Moving*> movingObjects;
std::vector<Agent*> actorObjects;
std::vector<Formation*> formations;
std::vector<void*> stufftobefreed;
std::vector<sf::FloatRect> obstacles;

int screenWidth = 1000;
int screenHeight = 1000;

void freeStuff()
{
	for(auto i : stufftobefreed)
	{
		delete i;
	}
}

void DebugRender(Renderable* obj, sf::RenderWindow* window)
{
	obj->DebugDraw(window);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	//Hardcoded
	//floor
	RenderObject* floor = new RenderObject("./Assets/floor.jpg", glm::vec2(screenWidth / 2, screenHeight / 2));
	renderObjects.push_back(floor);
	stufftobefreed.push_back(floor);
	
	//Obstacles
	Wall* wall = new Wall(glm::vec2(screenHeight * (4.0f/5.0f) , screenWidth * (4.0f/5.0f)));
	renderObjects.push_back(wall);
	obstacles.push_back(wall->GetBoundingBox());
	stufftobefreed.push_back(wall);

	//Path
	Path* path = new Path();
	renderObjects.push_back(path);
	stufftobefreed.push_back(path);

	//Formation
	Formation* wedgeFormation = new WedgeFormation();
	wedgeFormation->SetPosition(glm::vec2(499.0f, 499.0f));
	wedgeFormation->SetPath(path);
	renderObjects.push_back(wedgeFormation);
	movingObjects.push_back(wedgeFormation);
	stufftobefreed.push_back(wedgeFormation);

	//Soldier
	Agent* tmp = new Agent("./Assets/soldier.png");
	tmp->setPosition(glm::vec2(498.0f, 498.0f));
	tmp->setFormation(wedgeFormation);
	renderObjects.push_back(tmp);
	movingObjects.push_back(tmp);
	actorObjects.push_back(tmp);
	stufftobefreed.push_back(tmp);

	//tmp = new Agent("./Assets/soldier.png");
	//tmp->setPosition(glm::vec2(497.0f, 497.0f));
	//tmp->setFormation(wedgeFormation);
	//renderObjects.push_back(tmp);
	//movingObjects.push_back(tmp);
	//actorObjects.push_back(tmp);
	//stufftobefreed.push_back(tmp);

	//tmp = new Agent("./Assets/soldier.png");
	//tmp->setPosition(glm::vec2(496.0f, 496.0f));
	//tmp->setFormation(wedgeFormation);
	//renderObjects.push_back(tmp);
	//movingObjects.push_back(tmp);
	//actorObjects.push_back(tmp);
	//stufftobefreed.push_back(tmp);

	//tmp = new Agent("./Assets/soldier.png");
	//tmp->setPosition(glm::vec2(495.0f, 495.0f));
	//tmp->setFormation(wedgeFormation);
	//renderObjects.push_back(tmp);
	//movingObjects.push_back(tmp);
	//actorObjects.push_back(tmp);
	//stufftobefreed.push_back(tmp);

	//Give list of actors for separation
	for(auto* a : actorObjects)
	{
		a->SetSeparationActors(&actorObjects);
		a->SetObstacles(&obstacles);
	}

	//Hardcoded End

	//Timer
	sf::Clock deltaClock;

	while (window.isOpen())
	{
		sf::Time deltaTime = deltaClock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Escape)
				{
					window.close();
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					for (auto i : actorObjects)
					{
						i->ToggleTargetType();
					}
				}
			}
		}

		window.clear();


		//Move stuff
		for(const auto& obj : movingObjects)
		{
			obj->Move(deltaTime);
		}

		//Render stuff
		for(auto obj : renderObjects)
		{
			DebugRender(obj, &window);
			obj->Render(&window);
		}

		window.display();
	}

	freeStuff();

	return 0;
}
