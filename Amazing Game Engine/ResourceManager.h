#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map> 

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, sf::Sprite*> images;

	void loadImageWithName(std::string name, std::string loaction);
	
};

