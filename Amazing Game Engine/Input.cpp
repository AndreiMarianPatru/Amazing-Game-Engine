#include "Input.h"


#include <b2_math.h>
#include <iostream>
#include <list>
#include <vector>
				//player->body->ApplyLinearImpulse(b2Vec2(-10, 0), player->body->GetWorldCenter(), true);

Input::Input()
{
	keyspressed=new std::map<states,std::string>();
}

void Input::CheckForInput(sf::Window& window)
{

	/*std::cout<<"keys pressed: "<<std::endl;
	std::map<std::string,states>::iterator it;
	for(it= keyspressed->begin();it!=keyspressed->end();++it)
	{
		std::cout<<it->first<<"  ";
		
	}
	std::cout<<std::endl;*/
	
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.key.code == sf::Keyboard::W)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
			
			 keyspressed->insert(std::pair<states,std::string>(jump,"W"));
			}				
			else if(event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed->erase(jump);
				
			}			
		}
		
		if (event.key.code == sf::Keyboard::A)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				
			 keyspressed->insert(std::pair<states,std::string>(left,"A"));
			}				
			else if(event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed->erase(left);
			
			}			
		}
		
		if (event.key.code == sf::Keyboard::D)
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
			
			 keyspressed->insert(std::pair<states,std::string>(right,"D"));
			}				
			else if(event.type == sf::Event::EventType::KeyReleased)
			{
				keyspressed->erase(right);
			
			}			
		}
		
	}
	
}

void Input::UseInput()
{
	
    
	
	
}
