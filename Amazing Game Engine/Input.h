#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Input
{
public:
	bool Rpressed;
	bool Tpressed;

	enum states
	{
		left,
		right,
		jump,
	};

	Input();
	std::map<states, std::string>* keyspressed;
	//I need a map and not a list for to make  key remapping easier to implement

	void CheckForInput(sf::Window& window);
	void UseInput();
};
