#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Input
{
public:
	
	enum states
	{
		left,
		right,
		jump
	};
	std::map<std::string,states> keyspressed;

	void CheckForInput(sf::Window &window);
	void UseInput();
	
};

