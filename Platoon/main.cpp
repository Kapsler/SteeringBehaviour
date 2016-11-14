#include <SFML/Graphics.hpp>
#include "RenderObject.h"
#include "Actor.h"
#include <glm/glm.hpp>
#include "WedgeFormation.h"
#include "Path.h"

std::vector<Renderable*> renderObjects;
std::vector<Moving*> movingObjects;
std::vector<Actor*> actorObjects;
std::vector<Formation*> formations;

int screenWidth = 1000;
int screenHeight = 1000;

void freeStuff()
{
	for(auto i : renderObjects)
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
	renderObjects.push_back(new RenderObject("./Assets/floor.jpg", glm::vec2(screenWidth / 2, screenHeight / 2)));

	//Path
	Path* path = new Path();
	renderObjects.push_back(path);

	//Formation
	Formation* wedgeFormation = new WedgeFormation();
	wedgeFormation->SetPosition(glm::vec2(499.0f, 499.0f));
	wedgeFormation->SetPath(path);
	renderObjects.push_back(wedgeFormation);
	movingObjects.push_back(wedgeFormation);

	//Soldier
	Actor* tmp = new Actor("./Assets/soldier.png", 0);
	tmp->setPosition(glm::vec2(498.0f, 498.0f));
	tmp->setFormation(wedgeFormation);
	renderObjects.push_back(tmp);
	movingObjects.push_back(tmp);
	actorObjects.push_back(tmp);

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
			} else if(event.key.code == sf::Keyboard::Space)
			{
				for(auto i : actorObjects)
				{
					i->ToggleTargetType();
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
