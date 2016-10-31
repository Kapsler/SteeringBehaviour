#include <SFML/Graphics.hpp>
#include "RenderObject.h"
#include "Actor.h"
#include <glm/glm.hpp>

std::vector<Renderable*> renderObjects;
std::vector<Moving*> movingObjects;

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

	//Soldier
	Actor* tmp = new Actor("./Assets/soldier.png");
	tmp->setPosition(glm::vec2(screenWidth / 4, screenHeight / 4));
	renderObjects.push_back(tmp);
	movingObjects.push_back(tmp);


	//Hardcoded End

	//Timer
	sf::Clock deltaClock;

	while (window.isOpen())
	{
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
			}
		}

		window.clear();


		//Move stuff
		for(auto obj : movingObjects)
		{
			obj->Move(deltaClock.restart());
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
