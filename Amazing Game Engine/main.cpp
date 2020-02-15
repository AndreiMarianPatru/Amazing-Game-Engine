#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "ResourceManager.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    ResourceManager* myresource_manager =new ResourceManager();
    myresource_manager->loadImageWithName("random", "assets/random.jpg");
    myresource_manager->loadImageWithName("flag","assets/flag.png");
    myresource_manager->loadSoundWithName("sound1", "assets/sound1.wav");

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
        for (auto image:myresource_manager->images)
        {
            window.draw(*image.second);
        }
        window.display();
    }

    return 0;
}