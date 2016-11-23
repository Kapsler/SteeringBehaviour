#include "Path.h"

Path::Path()
{
}

Path::~Path()
{
}

void Path::Render(sf::RenderWindow* window)
{
}

void Path::DebugDraw(sf::RenderWindow* window)
{
	sf::Vertex* line = new sf::Vertex[2];

	for(int i = 0; i < waypoints.size(); ++i)
	{
		//Point
		sf::CircleShape pt;
		pt.setRadius(5);
		pt.setOrigin(pt.getRadius(), pt.getRadius());
		pt.move(waypoints[i].x, waypoints[i].y);
		pt.setFillColor(sf::Color::Yellow);

		window->draw(pt);

		//Line
		if (i + 1 < waypoints.size())
		{
			sf::Vector2f tmp1(waypoints[i].x, waypoints[i].y);
			line[0] = sf::Vertex(tmp1, sf::Color::Yellow);
			sf::Vector2f tmp2(waypoints[i+1].x, waypoints[i+1].y);
			line[1] = sf::Vertex(tmp2, sf::Color::Yellow);
			window->draw(line, 2, sf::LineStrip);
		}
	}

	delete[] line;
	
}

void Path::AddPoint(glm::vec2 newpoint)
{
	waypoints.push_back(newpoint);
}

glm::vec2 Path::GetPoint(int index)
{
	if(index < waypoints.size())
	{
		return waypoints[index];
	} if(cycle)
	{
		return waypoints[index%waypoints.size()];
	} else
	{
		return waypoints[waypoints.size() - 1];
	}
}

void Path::SetCycle(bool newstate)
{
	cycle = newstate;
}
