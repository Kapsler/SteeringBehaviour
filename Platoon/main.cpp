#include <SFML/Graphics.hpp>
#include "RenderObject.h"
#include "Agent.h"
#include <glm/glm.hpp>
#include "WedgeFormation.h"
#include "Path.h"
#include "Wall.h"
#include "Crate.h"

std::vector<Renderable*> renderObjects;
std::vector<Moving*> movingObjects;
std::vector<Agent*> actorObjects;
std::vector<Agent*> separationObjects;
std::vector<Agent*> enemyObjects;
std::vector<Formation*> formations;
std::vector<void*> stufftobefreed;
std::vector<sf::RectangleShape> obstacles;

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

void InitEnemies()
{
	//Enemy Path 1
	Path* enemyPath = new Path();
	enemyPath->AddPoint(glm::vec2(502.0f, 270.0f));
	enemyPath->AddPoint(glm::vec2(499.0f, 500.0f));
	enemyPath->SetCycle(true);
	renderObjects.push_back(enemyPath);
	stufftobefreed.push_back(enemyPath);

	//Enemy Formation 1
	Formation* enemyFormation = new Formation();
	enemyFormation->SetPosition(glm::vec2(501.0f, 271.0f));
	enemyFormation->SetPath(enemyPath);
	renderObjects.push_back(enemyFormation);
	movingObjects.push_back(enemyFormation);
	stufftobefreed.push_back(enemyFormation);

	//Enemie 1
	Agent* enemy = new Agent("./Assets/zombie.png");
	enemy->setPosition(glm::vec2(500.0f, 271.0f));
	enemy->setFormation(enemyFormation);
	renderObjects.push_back(enemy);
	enemyObjects.push_back(enemy);
	separationObjects.push_back(enemy);
	movingObjects.push_back(enemy);
	stufftobefreed.push_back(enemy);

	//Enemy Path 2
	Path* enemyPath2 = new Path();
	enemyPath2->AddPoint(glm::vec2(502.0f, 50.0f));
	enemyPath2->AddPoint(glm::vec2(499.0f, 250.0f));
	enemyPath2->SetCycle(true);
	renderObjects.push_back(enemyPath2);
	stufftobefreed.push_back(enemyPath2);

	//Enemy Formation 2
	Formation* enemyFormation2 = new Formation();
	enemyFormation2->SetPosition(glm::vec2(501.0f, 251.0f));
	enemyFormation2->SetPath(enemyPath2);
	renderObjects.push_back(enemyFormation2);
	movingObjects.push_back(enemyFormation2);
	stufftobefreed.push_back(enemyFormation2);

	//Enemie 2
	Agent *enemy2 = new Agent("./Assets/zombie.png");
	enemy2->setPosition(glm::vec2(500.0f, 52.0f));
	enemy2->setFormation(enemyFormation2);
	renderObjects.push_back(enemy2);
	enemyObjects.push_back(enemy2);
	separationObjects.push_back(enemy2);
	movingObjects.push_back(enemy2);
	stufftobefreed.push_back(enemy2);

	//Enemy Path 3
	Path* enemyPath3 = new Path();
	enemyPath3->AddPoint(glm::vec2(102.0f, 650.0f));
	enemyPath3->AddPoint(glm::vec2(103.0f, 350.0f));
	enemyPath3->SetCycle(true);
	renderObjects.push_back(enemyPath3);
	stufftobefreed.push_back(enemyPath3);

	//Enemy Formation 3
	Formation* enemyFormation3 = new Formation();
	enemyFormation3->SetPosition(glm::vec2(104.0f, 351.0f));
	enemyFormation3->SetPath(enemyPath3);
	renderObjects.push_back(enemyFormation3);
	movingObjects.push_back(enemyFormation3);
	stufftobefreed.push_back(enemyFormation3);

	//Enemie 3
	Agent *enemy3 = new Agent("./Assets/zombie.png");
	enemy3->setPosition(glm::vec2(100.0f, 350.0f));
	enemy3->setFormation(enemyFormation3);
	renderObjects.push_back(enemy3);
	enemyObjects.push_back(enemy3);
	separationObjects.push_back(enemy3);
	movingObjects.push_back(enemy3);
	stufftobefreed.push_back(enemy3);

	//Enemy Path 4
	Path* enemyPath4 = new Path();
	enemyPath4->AddPoint(glm::vec2(300.0f, 700.0f));
	enemyPath4->AddPoint(glm::vec2(800.0f, 850.0f));
	enemyPath4->SetCycle(true);
	renderObjects.push_back(enemyPath4);
	stufftobefreed.push_back(enemyPath4);

	//Enemy Formation 4
	Formation* enemyFormation4 = new Formation();
	enemyFormation4->SetPosition(glm::vec2(800.0f, 851.0f));
	enemyFormation4->SetPath(enemyPath4);
	renderObjects.push_back(enemyFormation4);
	movingObjects.push_back(enemyFormation4);
	stufftobefreed.push_back(enemyFormation4);

	//Enemie 4
	Agent *enemy4 = new Agent("./Assets/zombie.png");
	enemy4->setPosition(glm::vec2(801.0f, 852.0f));
	enemy4->setFormation(enemyFormation4);
	renderObjects.push_back(enemy4);
	enemyObjects.push_back(enemy4);
	separationObjects.push_back(enemy4);
	movingObjects.push_back(enemy4);
	stufftobefreed.push_back(enemy4);

	//Enemy Path 5
	Path* enemyPath5 = new Path();
	enemyPath5->AddPoint(glm::vec2(550.0f, 451.0f));
	enemyPath5->AddPoint(glm::vec2(800.0f, 452.0f));
	enemyPath5->SetCycle(true);
	renderObjects.push_back(enemyPath5);
	stufftobefreed.push_back(enemyPath5);

	//Enemy Formation 5
	Formation* enemyFormation5 = new Formation();
	enemyFormation5->SetPosition(glm::vec2(551.0f, 453.0f));
	enemyFormation5->SetPath(enemyPath5);
	renderObjects.push_back(enemyFormation5);
	movingObjects.push_back(enemyFormation5);
	stufftobefreed.push_back(enemyFormation5);

	//Enemie 5
	Agent *enemy5 = new Agent("./Assets/zombie.png");
	enemy5->setPosition(glm::vec2(552.0f, 454.0f));
	enemy5->setFormation(enemyFormation5);
	renderObjects.push_back(enemy5);
	enemyObjects.push_back(enemy5);
	separationObjects.push_back(enemy5);
	movingObjects.push_back(enemy5);
	stufftobefreed.push_back(enemy5);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Platoon");
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	//Hardcoded
	//floor
	RenderObject* floor = new RenderObject("./Assets/floor.jpg", glm::vec2(screenWidth / 2, screenHeight / 2));
	renderObjects.push_back(floor);
	stufftobefreed.push_back(floor);

	//finish
	RenderObject* finish = new RenderObject("./Assets/target.png", glm::vec2(825.0f, 150.0f));
	renderObjects.push_back(finish);
	stufftobefreed.push_back(finish);
	
	//Obstacles
	Wall* wall;
	
	//Corner 1
	wall = new Wall(glm::vec2(screenHeight * (3.5f / 5.0f), screenWidth * (2.0f / 5.0f)));
	wall->Scale(1.8f, 1.0f);
	renderObjects.push_back(wall);
	obstacles.push_back(wall->GetBoundingBox());
	stufftobefreed.push_back(wall);

	//Corner 2
	wall = new Wall(glm::vec2(screenHeight * (8.5f / 10.0f), screenWidth * (5.5f / 10.0f)));
	wall->Scale(1.8f, 1.0f);
	wall->Rotate(90.0f);
	renderObjects.push_back(wall);
	obstacles.push_back(wall->GetBoundingBox());
	stufftobefreed.push_back(wall);

	Crate* crate;

	//Middle Group start
	crate = new Crate(glm::vec2(screenHeight * (0.9f / 2.0f), screenWidth * (1.1f / 2.0f)));
	crate->Scale(0.8f, 0.5f);
	crate->Rotate(-20);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);

	crate = new Crate(glm::vec2(screenHeight * (1.1f / 2.0f), screenWidth * (1.3f / 2.0f)));
	crate->Scale(0.8f, 0.5f);
	crate->Rotate(35);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);

	crate = new Crate(glm::vec2(screenHeight * (0.85f / 2.0f), screenWidth * (1.3f / 2.0f)));
	crate->Scale(0.8f, 0.5f);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);

	crate = new Crate(glm::vec2(screenHeight * (1.4f / 2.0f), screenWidth * (1.5f / 2.0f)));
	crate->Scale(0.8f, 0.5f);
	crate->Rotate(25);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);
	//Middle Group end

	//Lower Group start
	crate = new Crate(glm::vec2(screenHeight * (0.5f / 2.0f), screenWidth * (1.65f / 2.0f)));
	crate->Scale(0.5f, 0.3f);
	crate->Rotate(-60);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);

	crate = new Crate(glm::vec2(screenHeight * (0.75f / 2.0f), screenWidth * (1.7f / 2.0f)));
	crate->Scale(0.5f, 0.3f);
	crate->Rotate(-60);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);

	crate = new Crate(glm::vec2(screenHeight * (1.0f / 2.0f), screenWidth * (1.75f / 2.0f)));
	crate->Scale(0.5f, 0.3f);
	crate->Rotate(-60);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);

	//Lower Group end

	//Top1
	crate = new Crate(glm::vec2(screenHeight * (1.0f / 3.0f), screenWidth * (1.6f / 20.0f)));
	crate->Scale(2.0f, 1.3f);
	crate->Rotate(10);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);

	//Top2
	crate = new Crate(glm::vec2(screenHeight * (1.0f / 3.0f), screenWidth * (3.0f / 10.0f)));
	crate->Scale(2.0f, 1.3f);
	crate->Rotate(-10);
	renderObjects.push_back(crate);
	obstacles.push_back(crate->GetBoundingBox());
	stufftobefreed.push_back(crate);

	//Soldier Path
	Path* soldierPath = new Path();
	soldierPath->AddPoint(glm::vec2(300.0f, 900.0f));
	soldierPath->AddPoint(glm::vec2(325.0f, 800.0f));
	soldierPath->AddPoint(glm::vec2(600.0f, 750.0f));
	soldierPath->AddPoint(glm::vec2(650.0f, 550.0f));
	soldierPath->AddPoint(glm::vec2(400.0f, 425.0f));
	soldierPath->AddPoint(glm::vec2(150.0f, 450.0f));
	soldierPath->AddPoint(glm::vec2(125.0f, 190.0f));
	soldierPath->AddPoint(glm::vec2(825.0f, 150.0f));
	renderObjects.push_back(soldierPath);
	stufftobefreed.push_back(soldierPath);

	//Soldier Formation
	Formation* soldierFormation = new WedgeFormation();
	soldierFormation->SetPosition(glm::vec2(100.0f, 899.0f));
	soldierFormation->SetPath(soldierPath);
	renderObjects.push_back(soldierFormation);
	movingObjects.push_back(soldierFormation);
	stufftobefreed.push_back(soldierFormation);

	//Soldier
	Agent* tmp = new Agent("./Assets/soldier.png");
	tmp->setPosition(glm::vec2(100.0f, 900.0f));
	tmp->setFormation(soldierFormation);
	renderObjects.push_back(tmp);
	separationObjects.push_back(tmp);
	movingObjects.push_back(tmp);
	actorObjects.push_back(tmp);
	stufftobefreed.push_back(tmp);

	tmp = new Agent("./Assets/soldier.png");
	tmp->setPosition(glm::vec2(101.0f, 901.0f));
	tmp->setFormation(soldierFormation);
	renderObjects.push_back(tmp);
	separationObjects.push_back(tmp);
	movingObjects.push_back(tmp);
	actorObjects.push_back(tmp);
	stufftobefreed.push_back(tmp);

	tmp = new Agent("./Assets/soldier.png");
	tmp->setPosition(glm::vec2(101.0f, 901.0f));
	tmp->setFormation(soldierFormation);
	renderObjects.push_back(tmp);
	separationObjects.push_back(tmp);
	movingObjects.push_back(tmp);
	actorObjects.push_back(tmp);
	stufftobefreed.push_back(tmp);

	tmp = new Agent("./Assets/soldier.png");
	tmp->setPosition(glm::vec2(101.0f, 901.0f));
	tmp->setFormation(soldierFormation);
	renderObjects.push_back(tmp);
	separationObjects.push_back(tmp);
	movingObjects.push_back(tmp);
	actorObjects.push_back(tmp);
	stufftobefreed.push_back(tmp);

	InitEnemies();

	//Give list of actors for separation
	for(auto* a : actorObjects)
	{
		a->SetSeparationActors(&separationObjects);
		a->SetObstacles(&obstacles);
		a->SetEnemys(&enemyObjects);
	}

	for (auto* e : enemyObjects)
	{
		e->SetObstacles(&obstacles);
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
		for(auto& obj : renderObjects)
		{
			obj->Render(&window);
			DebugRender(obj, &window);
		}

		window.display();
	}

	freeStuff();

	return 0;
}
