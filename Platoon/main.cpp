#include <SFML/Graphics.hpp>
#include "RenderObject.h"

std::vector<RenderObject*> renderObjects;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");	
	window.setKeyRepeatEnabled(false);

	//Hardcoded
	renderObjects.push_back(new RenderObject("./Assets/floor.jpg"));
	//Hardcoded End

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


		//Render stuff
		for(auto obj : renderObjects)
		{
			obj->Render(&window);
		}

		window.display();
	}

	return 0;
}
