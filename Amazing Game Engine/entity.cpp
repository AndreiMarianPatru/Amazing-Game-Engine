#include "entity.h"


std::vector<BaseEntity*> BaseEntity::Renderables;

Object::Object(int id)
{
	this->id = id;
}

Object::Object()
{
}

Object::~Object()
{
}

void Object::SetParent(Object* parent)
{
	this->parent = parent;
}


Object* Object::GetParent()
{
	if (this->parent != nullptr)
	{
		return this->parent;
	}
	return nullptr;
}

void Object::SetTransform(b2Transform newTransform)
{
	this->transform = newTransform;
}

b2Transform Object::GetTransform()
{
	return this->transform;
}

void Object::AddChild(Object* object)
{
	this->children.push_back(object);
}

void Object::RemoveChild(int m_id)
{
	std::list<Object*>::iterator it;

	for (it = this->children.begin(); it != this->children.end();)
	{
		if ((*it)->id == m_id)
		{
			delete *it;
			it = this->children.erase(it);
		}
		else
		{
			++it;
		}
	}
}


void Object::Update(std::map<Input::states, std::string>* keyspressed)
{
}

void Object::UpdateChildren()
{
}

void Object::PrintChildren()
{
	std::cout << "children list size " << this->children.size() << std::endl;
	std::list<Object*>::iterator it;

	for (it = this->children.begin(); it != this->children.end(); ++it)
	{
		std::cout << ((*it)->id) << std::endl;
	}
}

BaseEntity::BaseEntity(b2World* world)
{
	this->world = world;
}


BaseEntity::~BaseEntity()
{
}

void BaseEntity::Think()
{
}

void BaseEntity::m_setposition(float x, float y)
{
	this->body->SetTransform(b2Vec2(x, y), 0);
	this->setPosition(x * SCALE, y * SCALE);
}

void BaseEntity::Update(std::map<Input::states, std::string>* keyspressed)
{
	this->setPosition(this->body->GetPosition().x * SCALE, this->body->GetPosition().y * SCALE);
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
	dynamicBox.SetAsBox((sprite.getTexture()->getSize().x / SCALE) / 2, (sprite.getTexture()->getSize().y / SCALE) / 2);
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
	dynamicBox.SetAsBox((sprite.getTexture()->getSize().x / SCALE) / 2, (sprite.getTexture()->getSize().y / SCALE) / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.1f;
	body->CreateFixture(&fixtureDef);
}


Player::Player(b2World* world): BaseEntity(world)
{
}

void Player::Update(std::map<Input::states, std::string>* keyspressed)
{
	b2Vec2 vel = body->GetLinearVelocity();
	float desiredVel = 0;
	std::map<std::string, Input::states>::iterator it;

	if (keyspressed->find(Input::left) != keyspressed->end())
		desiredVel -= b2Max(vel.x - 0.1f, +10.0f);
	if (keyspressed->find(Input::right) != keyspressed->end())
		desiredVel += b2Max(vel.x - 0.1f, +10.0f);
	if (keyspressed->find(Input::jump) != keyspressed->end() && vel.y == 0)
		body->ApplyLinearImpulse(b2Vec2(0, -450), body->GetWorldCenter(), true);


	float velChange = desiredVel - vel.x;
	float impulsex = body->GetMass() * velChange; //disregard time factor

	body->ApplyLinearImpulse(b2Vec2(impulsex, 0), body->GetWorldCenter(), true);


	this->setPosition(this->body->GetPosition().x * SCALE, this->body->GetPosition().y * SCALE);
	// this->setRotation(this->body->GetAngle());
	//this->sprite.setRotation(this->getRotation());	
}
