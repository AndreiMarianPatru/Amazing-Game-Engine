#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "entity.h"
#include "box2d.h"
#include <stdio.h>

using namespace std;



int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
	window.setFramerateLimit(60);

    // Define the gravity vector.
	b2Vec2 gravity(0.0f, 10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 30.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

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

	
    ResourceManager* resource_manager =new ResourceManager();
    resource_manager->loadImageWithName("random", "assets/random.jpg");
    resource_manager->loadImageWithName("flag","assets/flag.png");
    resource_manager->loadSoundWithName("sound1", "assets/sound1.wav");


	BaseEntity* player = new BaseEntity(&world);
    player->setSprite(resource_manager->searchForImage("random"));
    player->m_setposition(10, 0);
    player->Initialize();
    resource_manager->playsound("sound1s");
    std::cout<<world.GetBodyCount();
	while (window.isOpen())
    {
	

        
    	
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        	 if (event.type == sf::Event::EventType::KeyPressed)
			 {
				if (event.key.code == sf::Keyboard::W)
				{
					std::cout<<"space";
					player->body->ApplyForce( b2Vec2(0,-2000), player->body->GetWorldCenter(),true );        
				 }
			 }
        	 if (event.type == sf::Event::EventType::KeyPressed)
			 {
				if (event.key.code == sf::Keyboard::D)
				{
					std::cout<<"space";
					player->body->ApplyLinearImpulse( b2Vec2(10,0), player->body->GetWorldCenter(),true );        
				 }
			 }
        	if (event.type == sf::Event::EventType::KeyPressed)
			 {
				if (event.key.code == sf::Keyboard::A)
				{
					std::cout<<"space";
					player->body->ApplyLinearImpulse( b2Vec2(-10,0), player->body->GetWorldCenter(),true );        
				 }
			 }
        }

        window.clear();

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		 window.clear();
		
	
		

		//std::cout<<player->body->GetPosition().x<<" "<<player->body->GetPosition().y<<std::endl;
	
      

        for (auto entity : BaseEntity::Renderables)
        {
        	entity->m_update();
            window.draw(entity->GetSprite(), entity->getTransform());
        	
        }
		
        window.display();
    }

    return 0;
}

