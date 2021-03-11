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

	Input();///basic constructor
	std::map<states, std::string>* keyspressed;///a map is used and not a list for to make  key remapping easier to implement
	

	void CheckForInput(sf::Window& window);///check if there is any new input from the keyboard, if there is any store it in the keyspressed map

};
