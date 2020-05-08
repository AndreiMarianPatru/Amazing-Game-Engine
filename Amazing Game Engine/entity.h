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

	int id{};
	std::string name;
	int ZOrder{};
	std::list<Object*> children;
	Object* parent;
	b2Transform transform;
	sf::Sprite sprite;
	sf::Texture texture;
	b2World* world;
	b2Body* body;


	Object(int id);
	Object();
	~Object();

	void SetParent(Object* parent);
	Object* GetParent();
	void SetTransform(b2Transform newTransform);

	b2Transform GetTransform();
	void AddChild(Object* object);
	void RemoveChild(int id);

	virtual void Update(std::map<Input::states, std::string>* keyspressed);
	virtual void UpdateChildren(b2Body* body);


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


	/**
	 * Base constructor, defaults all variables.
	 */
	BaseEntity(b2World* world);
	/**
	 * Constructor that accepts a texture file name
	 * @param file a string filename
	 */

	/**
	 * Deconstructor
	 */
	virtual ~BaseEntity();

	
	virtual void Initialize();





	void Update(std::map<Input::states, std::string>* keyspressed) override;
	void UpdateChildren(b2Body* body) override;

	void setSprite(sf::Sprite newsprite);
	void m_setshapeb2d();
	void m_setfrictionb2d(float value);
public:
	

};

class Player : public BaseEntity
{
public:


	Player(b2World* world);
	void Update(std::map<Input::states, std::string>* keyspressed) override;
};
