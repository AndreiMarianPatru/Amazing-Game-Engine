#include "Input.h"


#include <b2_math.h>
#include <iostream>
#include <list>
#include <vector>
//player->body->ApplyLinearImpulse(b2Vec2(-10, 0), player->body->GetWorldCenter(), true);

Input::Input()
{
	keyspressed = new std::map<states, std::string>();
}

void Input::CheckForInput(sf::Window& window)
{
	sf::Event event{};
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.key.code == sf::Keyboard::W)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				keyspressed->insert(std::pair<states, std::string>(jump, "W"));
			}
			else if (event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed->erase(jump);
			}
		}

		if (event.key.code == sf::Keyboard::A)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				keyspressed->insert(std::pair<states, std::string>(left, "A"));
			}
			else if (event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed->erase(left);
			}
		}

		if (event.key.code == sf::Keyboard::D)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				keyspressed->insert(std::pair<states, std::string>(right, "D"));
			}
			else if (event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed->erase(right);
			}
		}

		if (event.key.code == sf::Keyboard::T)
		{
			
		     if (event.type == sf::Event::EventType::KeyReleased)
			{
				Tpressed=true;
			}
		}
		if (event.key.code == sf::Keyboard::R)
		{
			if (event.type == sf::Event::EventType::KeyReleased)
			{
				Rpressed=true;
			}
		}
	}
}

void Input::UseInput()
{
}
