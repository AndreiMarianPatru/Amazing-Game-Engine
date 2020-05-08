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

void inline setScene1(Player& player,BaseEntity& enemy1, BaseEntity& enemy2)
{
	
	player.m_setposition(10, 10);
	enemy1.m_setposition(20, 15);
	enemy2.m_setposition(20, 5);
	

}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
	window.setFramerateLimit(60);
	Input* input = new Input();

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
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


	//// Define the dynamic body. We set its position and call the body factory.
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	//b2Body* body = world.CreateBody(&bodyDef);

	//// Define another box shape for our dynamic body.
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);
	//

	//// Define the dynamic body fixture.
	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;

	//// Set the box density to be non-zero, so it will be dynamic.
	//fixtureDef.density = 1.0f;

	//// Override the default friction.
	//fixtureDef.friction = 0.3f;

	//// Add the shape to the body.
	//body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	// This is our little game loop.
	//for (int32 i = 0; i < 600; ++i)
	//{
	//	
	//}

	/*When the world destructor is called, all bodies and joints are freed. This can
	create orphaned pointers, so be careful about your world management.*/

	//CHECK(b2Abs(position.x) < 0.01f);
	//CHECK(b2Abs(position.y - 1.01f) < 0.01f);
	//CHECK(b2Abs(angle) < 0.01f);
	SceneManager scene_manager;
	Scene scene1=Scene(1);
	Scene scene2=Scene(2);

	ResourceManager resource_manager;
	resource_manager.loadImageWithName("random", "assets/random.jpg");
	resource_manager.loadImageWithName("flag", "assets/flag.png");
	resource_manager.loadImageWithName("bob", "assets/bob.png");
	resource_manager.loadSoundWithName("sound1", "assets/sound1.wav");
	resource_manager.loadImageWithName("ground", "assets/ground2.png");

	Object ground;
	ground.SetSprite(resource_manager.searchForImage("ground"));
	ground.setPosition(0, 850);
	ground.setScale(3.6f, 1.0f);
	std::shared_ptr<Object> S1ground(&ground);//create a copy for scene1
	

	
	Player player(world);
	player.setSprite(resource_manager.searchForImage("bob"));
	player.Initialize();
	player.m_setposition(10, 10);
	//player->m_setshapeb2d();
	player.m_setfrictionb2d(2.0f);
	std::shared_ptr<Player> S1player(&player);//create a copy for scene1
	

	
	BaseEntity enemy1(world);
	enemy1.setSprite(resource_manager.searchForImage("bob"));
	enemy1.Initialize();
	enemy1.m_setposition(20, 10);
	//enemy1->m_setshapeb2d();
	enemy1.m_setfrictionb2d(2.0f);
	std::shared_ptr<BaseEntity> S1enemy1(&enemy1);//create a copy for scene1
	


	BaseEntity enemy2(world);
	enemy2.setSprite(resource_manager.searchForImage("bob"));
	enemy2.Initialize();
	enemy2.m_setposition(20, 5);
	//enemy1->m_setshapeb2d();
	enemy2.m_setfrictionb2d(2.0f);
	std::shared_ptr<BaseEntity> S1enemy2(&enemy2);//create a copy for scene1

	scene1.AddObjectToScene(S1ground);
	scene1.AddObjectToScene(S1player);
	scene1.AddObjectToScene(S1enemy1);
	scene1.AddObjectToScene(S1enemy2);

	scene_manager.AddScene(&scene1);
	//scene_manager.LoadScene(1);
	scene2.AddObjectToScene(S1ground);
	scene2.AddObjectToScene(S1player);
	scene2.AddObjectToScene(S1enemy1);

	scene_manager.AddScene(&scene2);
	scene_manager.LoadScene(1);
	
	//a static body
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


	Object* root = new Object();
	Object* ob1 = new Object(1);
	Object* ob2 = new Object(2);
	Object* ob3 = new Object(3);
	Object* ob4 = new Object(4);
	Object* ob5 = new Object(5);
	root->AddChild(ob1);
	root->AddChild(ob2);
	root->AddChild(ob3);
	root->AddChild(ob4);
	root->AddChild(ob5);
	root->PrintChildren();
	std::cout << std::endl;
	root->RemoveChild(2);
	root->RemoveChild(20);
	root->PrintChildren();


	resource_manager.playsound("sound1");
	//  std::cout<<world->GetBodyCount();
	while (window.isOpen())
	{
		input->CheckForInput(window);


		window.clear();

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world->Step(timeStep, velocityIterations, positionIterations);

		window.clear();

		if(input->Rpressed)
		{
			std::cout<<"r";
	      scene_manager.LoadScene(1);
			setScene1(player,enemy1,enemy2);
			
		}

		//std::cout<<player->body->GetPosition().x<<" "<<player->body->GetPosition().y;

		//player->setRotation(player->getRotation()+1);

	//	window.draw(ground->GetSprite());

		for (auto entity : SceneManager::activeObjects)
		{
			entity->Update(input->keyspressed);
			window.draw(entity->GetSprite(), entity->getTransform());
		}
		window.display();
	}

	return 0;
}
