#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadImageWithName(std::string name, std::string location)
{
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(location);
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*texture);
	images.insert(std::pair<std::string, sf::Sprite*>(name, sprite));
}

void ResourceManager::loadSoundWithName(std::string name, std::string location)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer;
	if (! buffer->loadFromFile(location))
	{
		std::cout << "error";
	}
	sf::Sound* sound = new sf::Sound;
	sound->setBuffer(*buffer);
	sounds.insert(std::pair<std::string, sf::Sound*>(name, sound));
}

sf::Sprite ResourceManager::searchForImage(std::string name)
{
	if (images.find(name) == images.end())
		std::cout << "image " << name << " not found";
	else
		return *images.find(name)->second;
}

void ResourceManager::playsound(std::string name)
{
	for (auto it = sounds.begin(); it != sounds.end(); ++it)
	{
		if (it->first == name)
		{
			it->second->play();
			return;
		}
	}
	std::cout << "there is no such sound like this " << name << std::endl;
}
