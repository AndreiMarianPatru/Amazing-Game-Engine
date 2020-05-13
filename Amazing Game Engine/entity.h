#pragma once

/**
 * BaseEntity, the basic building block of any AI agent in the framework.
 *
 * This is the parent class for any agents desired to be added to the system,
 * it inherits from sf::Transformable to give us access to set / get position and related functionality.
 */

#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <box2d.h>
#include "Input.h"
#include <list>
static const float SCALE = 30.f;


// we need to tell the compiler that it's ok to use the default defines from math.h, if we don't, we don't get access to M_PI!
#define _USE_MATH_DEFINES


class Object : public sf::Transformable
{
public:

	int id;
	std::string name;
	int ZOrder{};
	std::list<Object*> children;
	Object* parent;
	b2Transform transform;
	sf::Sprite sprite;
	sf::Texture texture;
	b2World* world;
	b2Body* body;
	bool readyToBeDeleted;


	Object(int id);
	Object(int id, b2World* world);
	Object(int id, std::string name,int ZOrder,sf::Sprite sprite,b2World*world);
	Object();
	~Object();

	void SetParent(Object* parent);
	Object* GetParent();
	void SetTransform(b2Transform newTransform);

	b2Transform GetTransform();
	void AddChild(Object* object);
	void RemoveChild(int id);

	virtual void Update(std::map<Input::states, std::string>* keyspressed);
	virtual void UpdateChildren(std::map<Input::states, std::string>* keyspressed);


	void m_setpositionb2d(float x, float y);

	void PrintChildren();
	void SetSprite(sf::Sprite sprite);
	sf::Sprite GetSprite();
	void SetTexture(sf::Texture texture);
	sf::Texture GetTexture();
};


class BaseEntity : public Object
{
public:

	bool flag;
	/**
	 * Base constructor, defaults all variables but the world.
	 */
	BaseEntity(b2World* world);
	/**
	 * full constructor, sets it, name, zorder, sprite and world
	 */
	BaseEntity(int id, std::string name,int ZOrder,sf::Sprite sprite,b2World*world);
	/**
	 * Deconstructor
	 */
	virtual ~BaseEntity();

	//creates and sets the physics 
	virtual void Initialize();


	//sets the logic used for enemy NPC, it is called each frame in the main loop
	void Update(std::map<Input::states, std::string>* keyspressed) override;

	void UpdateChildren(std::map<Input::states, std::string>* keyspressed) override;

	//sets the sprite for this entity 
	void setSprite(sf::Sprite newsprite);

	//set the position. It uses box2d coords( real coords/scale). sets position for the physics body and updates the position drawn body
	void m_setshapeb2d();

	//set the friction for the physics body
	void m_setfrictionb2d(float value);
public:
};

class Player : public BaseEntity
{
public:

	Player(b2World* world);
	Player(int id, std::string name,int ZOrder,sf::Sprite sprite,b2World*world);
	void Update(std::map<Input::states, std::string>* keyspressed) override;
};

class Collectable : public Object
{
public:
	Collectable(int id, b2World* world);
	Collectable(int id, std::string name,int ZOrder,sf::Sprite sprite,b2World*world);
	~Collectable();
	void Initialize();
	void Update(std::map<Input::states, std::string>* keyspressed) override;
};
