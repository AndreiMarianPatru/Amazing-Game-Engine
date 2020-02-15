#include "ResourceManager.h"
#include <iostream>

ResourceManager::ResourceManager()
{
}

void ResourceManager::loadImageWithName(std::string name,std::string location)
{
    sf::Texture* texture=new sf::Texture;
    texture->loadFromFile(location);
    sf::Sprite* sprite=new sf::Sprite();
    sprite->setTexture(*texture);
    images.insert(std::pair<std::string, sf::Sprite*>(name, sprite));
}

void ResourceManager::loadSoundWithName(std::string name, std::string location)
{
    
    sf::SoundBuffer* buffer=new sf::SoundBuffer;
   if(! buffer->loadFromFile(location))
   {
       std::cout << "error";
   }
   sf::Sound* sound=new sf::Sound;
    sound->setBuffer(*buffer);
    sounds.insert(std::pair<std::string, sf::Sound*>(name, sound));
}
