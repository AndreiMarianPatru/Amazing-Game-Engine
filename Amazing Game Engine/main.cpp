#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>

#include "ResourceManager.h"
#include "entity.h"
#include "box2d.h"
#include <stdio.h>
#include "Input.h"
#include "Scene.h"


using namespace std;
float screenWidth = 1500;
float screenHeight = 1000;

ResourceManager resource_manager;

void inline setScene1(Player& player, BaseEntity& enemy1)
{
	player.m_setpositionb2d(10, 24);
	enemy1.m_setpositionb2d(20, 24);
	//	enemy2.m_setpositionb2d(25, 24);
}

void inline setScene2(Player& player, BaseEntity& enemy1, BaseEntity& enemy2)
{
	player.m_setpositionb2d(3, 24);
	enemy1.m_setpositionb2d(10, 24);
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
	window.setFramerateLimit(60);
	Input* input = new Input();

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	/*When the world destructor is called, all bodies and joints are freed. This can
	create orphaned pointers.*/
	b2World* world = new b2World(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 37.5f);


	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(500.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	SceneManager scene_manager;
	Scene scene1 = Scene(1);
	Scene scene2 = Scene(2);

	ResourceManager resource_manager;
	resource_manager.loadImageWithName("random", "assets/random.jpg");
	resource_manager.loadImageWithName("flag", "assets/flag.png");
	resource_manager.loadImageWithName("bob", "assets/bob.png");
	resource_manager.loadSoundWithName("sound1", "assets/sound1.wav");
	resource_manager.loadImageWithName("ground", "assets/ground2.png");
	resource_manager.loadImageWithName("enemy","assets/enemy.png");
	resource_manager.loadImageWithName("coin", "assets/coin.png");


	Object ground(0,"ground",0,resource_manager.searchForImage("ground"),world);
	ground.setPosition(0, 770);
	ground.setScale(3.6f, 1.5f);
	std::shared_ptr<Object> copyground(&ground);

	Collectable coin(1,"coin",3,resource_manager.searchForImage("coin"),world);
	coin.setPosition(800, 600);
	coin.setScale(0.2, 0.2);
	coin.Initialize();
	std::shared_ptr<Object> copycoin(&coin);

	Player player(2,"player",2,resource_manager.searchForImage("bob"),world);
	player.Initialize();
	player.m_setfrictionb2d(2.0f);
	std::shared_ptr<Player> copyplayer(&player);


	BaseEntity enemy1(3,"enemy",2,resource_manager.searchForImage("bob"),world);
	enemy1.Initialize();
	//enemy1.setScale(0.1f,0.1f);
	enemy1.name = "enemy1";


	enemy1.m_setfrictionb2d(2.0f);
	std::shared_ptr<BaseEntity> copyenemy1(&enemy1);


	/*BaseEntity enemy2(world);
	enemy2.setSprite(resource_manager.searchForImage("bob"));
	enemy2.Initialize();
	enemy2.name = "enemy2";*/


	//enemy2.m_setfrictionb2d(2.0f);
	//std::shared_ptr<BaseEntity> copyenemy2(&enemy2);

	scene1.AddObjectToScene(copyground);
	scene1.AddObjectToScene(copyplayer);
	scene1.AddObjectToScene(copyenemy1);
	//scene1.AddObjectToScene(copyenemy2);
	scene1.AddObjectToScene(copycoin);


	scene2.AddObjectToScene(copyground);
	scene2.AddObjectToScene(copyplayer);
	scene2.AddObjectToScene(copyenemy1);

	scene_manager.AddScene(&scene1);
	scene_manager.AddScene(&scene2);

	scene_manager.LoadScene(1);
	setScene1(player, enemy1);

	//create invisible walls
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	b2Body* staticBody = world->CreateBody(&myBodyDef);
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(1, 1);
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;


	polygonShape.SetAsBox(20, 1, b2Vec2(25, screenHeight / SCALE), 0); //ceiling
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(1, 20, b2Vec2(-(SCALE / 10), 20), 0); //left wall
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(1, 20, b2Vec2((screenWidth / SCALE) - 1, 20), 0); //right wall
	staticBody->CreateFixture(&myFixtureDef);


	//enemy1.AddChild(&enemy2);


	while (window.isOpen())
	{
		input->CheckForInput(window);


		window.clear();

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world->Step(timeStep, velocityIterations, positionIterations);

		window.clear();

		if (input->Rpressed)
		{
			std::cout << "R";
			scene_manager.LoadScene(1);
			//setScene1(player, enemy1, enemy2);
			resource_manager.playsound("sound1");
			input->Rpressed = false;
		}
		if (input->Tpressed)
		{
			std::cout << "T";
			scene_manager.LoadScene(2);
			//setScene2(player, enemy1, enemy2);
			resource_manager.playsound("sound1");
			input->Tpressed = false;
		}


		for (auto entity : scene_manager.activeObjects)
		{
			entity->Update(input->keyspressed);
			entity->UpdateChildren(input->keyspressed);
			window.draw(entity->GetSprite(), entity->getTransform());
		}
		for (auto entity : scene_manager.activeObjects)
		{
			if (entity->readyToBeDeleted)
			{
				entity->world->DestroyBody(entity->body);
				scene_manager.activeObjects.remove(entity);
				break;
			}
		}
		//scene_manager.activeObjects.clear();
		window.display();
	}

	return 0;
}
