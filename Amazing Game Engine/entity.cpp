#include "entity.h"



std::vector<BaseEntity*> BaseEntity::Renderables;

Object::Object()
{
}

Object::~Object()
{
}

void Object::SetParent()
{
}

Object* Object::GetParent()
{
}

void Object::SetTransform(b2Transform* newTransform)
{
	
}

b2Transform Object::GetTransform()
{
}

void Object::AddChild(Object* object)
{
}

void Object::RemoveChild(int id)
{
}

void Object::Update()
{
}

void Object::UpdateChildren()
{
}

BaseEntity::BaseEntity(b2World* world)
{
		this->world=world;
	
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

void BaseEntity::m_update(std::map<Input::states,std::string>* keyspressed)
{

	
     this->setPosition(this->body->GetPosition().x*SCALE,this->body->GetPosition().y*SCALE);
	 this->setRotation(this->body->GetAngle());
	 this->sprite.setRotation(this->getRotation());	}

void BaseEntity::setSprite(sf::Sprite newsprite)
{
	sprite = newsprite;
}

void BaseEntity::m_setshapeb2d()
{
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((sprite.getTexture()->getSize().x/SCALE)/2, (sprite.getTexture()->getSize().y/SCALE)/2);
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
	
	Renderables.push_back(this);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	this->body = this->world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((sprite.getTexture()->getSize().x/SCALE)/2, (sprite.getTexture()->getSize().y/SCALE)/2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
	body->CreateFixture(&fixtureDef);		
}


Player::Player(b2World* world): BaseEntity(world)
{
	
}

void Player::m_update(std::map< Input::states,std::string>* keyspressed)
{
	b2Vec2 vel = body->GetLinearVelocity();
    float desiredVel = 0;
	std::map<std::string, Input::states>::iterator it;

	if(keyspressed->find(Input::left)!=keyspressed->end())
		desiredVel-=b2Max( vel.x - 0.1f, +10.0f );
	if(keyspressed->find(Input::right)!=keyspressed->end())
		desiredVel+=b2Max( vel.x - 0.1f, +10.0f );
	if(keyspressed->find(Input::jump)!=keyspressed->end()&&vel.y==0)
		 body->ApplyLinearImpulse( b2Vec2(0,-450), body->GetWorldCenter(),1);


	float velChange = desiredVel - vel.x;
    float impulsex = body->GetMass() * velChange; //disregard time factor

    body->ApplyLinearImpulse( b2Vec2(impulsex,0), body->GetWorldCenter(),1);
	
	
     this->setPosition(this->body->GetPosition().x*SCALE,this->body->GetPosition().y*SCALE);
	// this->setRotation(this->body->GetAngle());
	 //this->sprite.setRotation(this->getRotation());	
}
