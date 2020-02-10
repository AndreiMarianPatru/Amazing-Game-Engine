#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

void ResourceManager::loadImageWithName(std::string name)
{
    sf::Texture* texture=new sf::Texture;
    texture->loadFromFile(name);
    sf::Sprite* sprite=new sf::Sprite;
    sprite->setTexture(*texture);
    images.push_back(*sprite);
}
