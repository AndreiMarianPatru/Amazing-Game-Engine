#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

void ResourceManager::loadImageWithName(std::string name,std::string loaction)
{
    sf::Texture* texture=new sf::Texture;
    texture->loadFromFile(loaction);
    sf::Sprite* sprite=new sf::Sprite();
    sprite->setTexture(*texture);
    images.insert(std::pair<std::string, sf::Sprite*>(name, sprite));
}
