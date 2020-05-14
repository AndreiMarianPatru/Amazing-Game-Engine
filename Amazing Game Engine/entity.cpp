#include "entity.h"


Object::Object(int id)
{
	this->id = id;
}

Object::Object(int id, b2World* world)
{
	this->id = id;
	this->world = world;
}

Object::Object(int id, std::string name, int ZOrder, sf::Sprite sprite, b2World* world)
{
	this->id=id;
	this->name=name;
	this->ZOrder=ZOrder;
	this->sprite=sprite;
	this->world=world;
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
	object->SetParent(this);
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

void Object::UpdateChildren(std::map<Input::states, std::string>* keyspressed)
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

void Object::SetSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}

sf::Sprite Object::GetSprite()
{
	return this->sprite;
}

void Object::SetTexture(sf::Texture texture)
{
	this->texture = texture;
}

sf::Texture Object::GetTexture()
{
	return this->texture;
}

BaseEntity::BaseEntity(b2World* world)
{
	this->world = world;
}

BaseEntity::BaseEntity(int id, std::string name, int ZOrder, sf::Sprite sprite, b2World* world)
{
	this->id=id;
	this->name=name;
	this->ZOrder=ZOrder;
	this->sprite=sprite;
	this->world=world;

}


BaseEntity::~BaseEntity()
{
}


void Object::m_setpositionb2d(float x, float y) //set position using b2d coords
{
	this->body->SetTransform(b2Vec2(x, y), 0);
	this->setPosition(x * SCALE, y * SCALE);
}

void BaseEntity::Update(std::map<Input::states, std::string>* keyspressed)
{
	

	switch (flag)
	{
	case true:
		
		body->ApplyLinearImpulse(b2Vec2(-5, 0), body->GetWorldCenter(), true);
		break;
	case false:
		
		body->ApplyLinearImpulse(b2Vec2(5, 0), body->GetWorldCenter(), true);
		break;
	}
	if (this->body->GetPosition().x > 30 && this->body->GetPosition().x < 31)
	{
		flag = true;
	}
	if (this->body->GetPosition().x > 0 && this->body->GetPosition().x < 1)
	{
		flag = false;
	}
	
	this->setPosition(this->body->GetPosition().x * SCALE, this->body->GetPosition().y * SCALE);
	this->setRotation(this->body->GetAngle());
	this->sprite.setRotation(this->getRotation());
}

void BaseEntity::UpdateChildren(std::map<Input::states, std::string>* keyspressed)
{
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
	flag = false;
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
	this->world = world;
}

Player::Player(int id, std::string name, int ZOrder, sf::Sprite sprite, b2World* world): BaseEntity(id,name,ZOrder,sprite,world)
{
	this->id = id;
	this->name = name;
	this->ZOrder = ZOrder;
	this->sprite = sprite;
	this->world = world;
}

void Player::Update(std::map<Input::states, std::string>* keyspressed)
{
	//std::cout<<"x "<<this->body->GetPosition().x<<" y "<<this->body->GetPosition().y<<std::endl;
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
	this->setRotation(this->body->GetAngle());
    this->sprite.setRotation(this->getRotation());	
}

Collectable::Collectable(int id, b2World* world)
{
	this->id = id;
	this->world = world;
	this->readyToBeDeleted = false;
}

Collectable::Collectable(int id, std::string name, int ZOrder, sf::Sprite sprite, b2World* world)
{
	this->id=id;
	this->name=name;
	this->ZOrder=ZOrder;
	this->sprite=sprite;
	this->world=world;
}

Collectable::~Collectable()
{
}


void Collectable::Initialize()
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(27, 19);
	this->body = world->CreateBody(&myBodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox(1, 1);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;
	fixtureDef.density = 0.0f;
	fixtureDef.isSensor = true;
	body->CreateFixture(&fixtureDef);
}

void Collectable::Update(std::map<Input::states, std::string>* keyspressed)
{
	if (this->readyToBeDeleted != true)
	{
		for (b2ContactEdge* ce = this->body->GetContactList(); ce; ce = ce->next)
		{
			b2Contact* c = ce->contact;
			if (c->IsTouching())
			{
				this->readyToBeDeleted = true;
			}
		}
	}
}
