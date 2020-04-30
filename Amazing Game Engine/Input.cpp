#include "Input.h"


#include <b2_math.h>
#include <iostream>
				//player->body->ApplyLinearImpulse(b2Vec2(-10, 0), player->body->GetWorldCenter(), true);

void Input::CheckForInput(sf::Window& window)
{
	std::cout<<"keys pressed: "<<std::endl;
	std::map<std::string,states>::iterator it;
	for(it= keyspressed.begin();it!=keyspressed.end();++it)
	{
		std::cout<<it->first<<"  ";
		
	}
	std::cout<<std::endl;
	
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.key.code == sf::Keyboard::W)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				std::cout << "w";
			 keyspressed.insert(std::pair<std::string, states>("W", jump));
			}				
			else if(event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed.erase("W");
				std::cout << " not w"<<std::endl;	
			}			
		}
		
		if (event.key.code == sf::Keyboard::A)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				std::cout << "A";
			 keyspressed.insert(std::pair<std::string, states>("A", jump));
			}				
			else if(event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed.erase("A");
				std::cout << " not A"<<std::endl;	
			}			
		}
		
		if (event.key.code == sf::Keyboard::D)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				std::cout << "D";
			 keyspressed.insert(std::pair<std::string, states>("D", jump));
			}				
			else if(event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed.erase("D");
				std::cout << " not D"<<std::endl;	
			}			
		}
		
	}
	
}

void Input::UseInput()
{
}
