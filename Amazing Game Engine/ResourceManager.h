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
	std::map<std::string, sf::Sound*> sounds;


	void loadImageWithName(std::string name, std::string location);
	void loadSoundWithName(std::string name, std::string location);
	sf::Sprite searchForImage(std::string name);
	
};

