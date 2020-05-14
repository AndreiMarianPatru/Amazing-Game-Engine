#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class ResourceManager
{
public:
	ResourceManager();//basic constructor
	~ResourceManager();//basic destructor

	std::map<std::string, sf::Sprite*> images;//this map will store a pair of names of images and the images themselves 
	std::map<std::string, sf::Sound*> sounds;//this map will store a pair of names of sounds and the sounds themselves 


	void loadImageWithName(std::string name, std::string location);//search a folder for an image by its name and if found, set a name for it and store it in images map
	void loadSoundWithName(std::string name, std::string location);//search a folder for a sound by its name and if found, set a name for it and store it in sounds map
	sf::Sprite searchForImage(std::string name);//search the images map for a specific image and return it 
	void playsound(std::string name);//search for a sound and if found play it
};
