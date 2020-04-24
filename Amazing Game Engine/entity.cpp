#include "entity.h"



std::vector<BaseEntity*> BaseEntity::Renderables;
BaseEntity::BaseEntity(b2World* world)
{
	// with no further information, we make some assumptions and set default values.
	filename = "assets\\boid.png";
	colourTint = sf::Color::White;
	this->world=world;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	this->body = this->world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

	
	
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

void BaseEntity::m_setposition(float x, float y)
{
	this->body->SetTransform(b2Vec2(x,y),0);
	this->setPosition(x*SCALE,y*SCALE);	
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


