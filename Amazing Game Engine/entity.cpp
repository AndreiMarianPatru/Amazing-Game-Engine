#include "entity.h"



std::vector<BaseEntity*> BaseEntity::Renderables;
BaseEntity::BaseEntity()
{
	// with no further information, we make some assumptions and set default values.
	filename = "assets\\boid.png";
	colourTint = sf::Color::White;

}

BaseEntity::BaseEntity(std::string file) : filename(file)
{
	// with just a texture file, we default to a white tint (so no tint at all).
	colourTint = sf::Color::White;
}

BaseEntity::BaseEntity(std::string file, sf::Color colour) : filename(file), colourTint(colour)
{

}

BaseEntity::~BaseEntity()
{

}

void BaseEntity::Think()
{
	// build a new position vector by adding a scaled version of the velocity vector
	sf::Vector2f pos = getPosition() + (velocity * 0.1f);
	// update our position
	setPosition(pos);
}

void BaseEntity::setSprite(sf::Sprite newsprite)
{
	sprite = newsprite;
}

void BaseEntity::Initialize()
{
	
	//// load the texture into memory
	//texture.loadFromFile(filename);
	//texture.setSmooth(true);
	//// and provide the sprite with a pointer to the texture object
	//// if the texture object is destroyed (goes out of scope etc) then the sprite will display weirdly
	//sprite.setTexture(texture);
	//// set up our colour tint
	//sprite.setColor(colourTint);

	

	// add the entity to the list of renderables.
	Renderables.push_back(this);
}


