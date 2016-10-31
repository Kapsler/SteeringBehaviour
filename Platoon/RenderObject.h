#pragma once
#include "Renderable.h"
#include <iostream>
#include <glm/glm.hpp>
using namespace std;

class RenderObject : public Renderable
{
public:
	RenderObject(std::string fileName);
	RenderObject(std::string fileName, glm::vec2 pos);
	RenderObject(const RenderObject& other);
	~RenderObject();

	void setPosition(glm::vec2 pos);


	void Render(sf::RenderWindow* window) override;
	void DebugDraw(sf::RenderWindow* window);

	sf::Texture texture;
	sf::Sprite sprite;
private:
};

