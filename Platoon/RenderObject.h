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

	void SetPosition(glm::vec2 pos);
	void SetRotation(float rot);
	void SetScale(float x, float y);
	void Scale(float x, float y);
	void Rotate(float rot);

	sf::RectangleShape GetBoundingBox() const;

	void Render(sf::RenderWindow* window) override;
	void DebugDraw(sf::RenderWindow* window);

	sf::Texture texture;
	sf::Sprite sprite;
private:
	sf::RectangleShape boundingbox;

};

