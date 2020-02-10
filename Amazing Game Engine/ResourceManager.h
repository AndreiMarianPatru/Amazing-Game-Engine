#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	std::vector<sf::Sprite> images;

	void loadImageWithName(std::string name);
	
};

