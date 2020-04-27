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
	dynamicBox.SetAsBox(1,1);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	body->CreateFixture(&fixtureDef);


	

	
	
}




BaseEntity::~BaseEntity()
{

}

void BaseEntity::Think()
{
	
}

void BaseEntity::m_setposition(float x, float y)
{
	this->body->SetTransform(b2Vec2(x,y),0);
	this->setPosition(x*SCALE,y*SCALE);	
}

void BaseEntity::m_update()
	{
		this->setPosition(this->body->GetPosition().x*SCALE,this->body->GetPosition().y*SCALE);
		this->setRotation(this->body->GetAngle());
	this->sprite.setRotation(this->getRotation());
	}

void BaseEntity::setSprite(sf::Sprite newsprite)
{
	sprite = newsprite;
}

void BaseEntity::m_setshapeb2d()
{
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(sprite.getTexture()->getSize().x/SCALE, sprite.getTexture()->getSize().y/SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	body->CreateFixture(&fixtureDef);

	
}

void BaseEntity::m_setfrictionb2d(float value)
{
	body->GetFixtureList()->SetFriction(value);
}

void BaseEntity::Initialize()
{
	
	
	
	
	

	// add the entity to the list of renderables.
	Renderables.push_back(this);
}


