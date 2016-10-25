#pragma once
#include "Renderable.h"
#include <iostream>
using namespace std;

class RenderObject : public Renderable
{
public:
	RenderObject(std::string fileName);
	RenderObject(const RenderObject& other);
	~RenderObject();

	void Render(sf::RenderWindow* window) override;

private:
};

