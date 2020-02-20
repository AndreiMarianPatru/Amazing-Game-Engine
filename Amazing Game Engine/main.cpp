#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "entity.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    ResourceManager* resource_manager =new ResourceManager();
    resource_manager->loadImageWithName("random", "assets/random.jpg");
    resource_manager->loadImageWithName("flag","assets/flag.png");
    resource_manager->loadSoundWithName("sound1", "assets/sound1.wav");
    BaseEntity* player = new BaseEntity();
    player->setSprite(resource_manager->searchForImage("random"));
    player->setPosition(100, 100);
    player->Initialize();
    //myresource_manager->sounds.begin()->second->play();
  
	while (window.isOpen())
    {

        
    	
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        for (auto image:resource_manager->images)
        {
            //window.draw(*image.second);
        }

        for (auto entity : BaseEntity::Renderables)
        {
            window.draw(entity->GetSprite(), entity->getTransform());
        }
        window.display();
    }

    return 0;
}