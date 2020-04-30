#include "Input.h"


#include <b2_math.h>
#include <iostream>

void Input::CheckForInput(sf::Window& window)
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
				std::cout << "w";
				
			}
		}
		if (event.type == sf::Event::EventType::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::W)
			{
				std::cout << " not w"<<std::endl;

			}
		}
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::D)
			{
				std::cout << "d";
				
			}
		}
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::A)
			{
				std::cout << "a";
				//player->body->ApplyLinearImpulse(b2Vec2(-10, 0), player->body->GetWorldCenter(), true);
			}
		}
	}
	
}
