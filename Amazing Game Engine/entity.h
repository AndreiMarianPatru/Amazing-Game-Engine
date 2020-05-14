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
	int ZOrder;//Zorder is used to render objects in a specific way so the most important objects are rendered last( are the closest to the user)
	std::list<Object*> children;//a list<Objects> to keep track of all the children of an object 
	Object* parent;
	b2Transform transform;
	sf::Sprite sprite;//the sprite associated with an object
	sf::Texture texture;
	b2World* world;//all physics run in an "object" of type b2World so each object must be connected to the same b2World 
	b2Body* body;//the "physics body" used by the physics engine, it is used for gravity, movement, collision detecting 
	bool readyToBeDeleted;//this is a "flag" that says if the object is ready to be deleted from the "active objects" scene

	Object();//most basic constructor, defaults everything
	Object(int id);//basic constructor sets just the id
	Object(int id, b2World* world);//this constructor sets the id and the links the object to the physics world 
	Object(int id, std::string name,int ZOrder,sf::Sprite sprite,b2World*world);//most advanced constructor, sets the id, name, ZOrder(which is the way in which the Objects are rendered,the sprite of the object and the physics world
	~Object();//default destructor 

	void SetParent(Object* parent);
	Object* GetParent();
	void SetTransform(b2Transform newTransform);

	b2Transform GetTransform();
	void AddChild(Object* object);
	void RemoveChild(int id);

	virtual void Update(std::map<Input::states, std::string>* keyspressed);//this it meant to be overwritten by each child class 
	virtual void UpdateChildren(std::map<Input::states, std::string>* keyspressed);//this it meant to be overwritten by each child class 


	void m_setpositionb2d(float x, float y);//set the position. It uses box2d coords( real coords/scale). sets position for the physics body and updates the position drawn body

	void PrintChildren();//debugging purposes, prints the id of each child
	void SetSprite(sf::Sprite sprite);//sets the sprite of an object
	sf::Sprite GetSprite();//returns the sprite of an Object
	void SetTexture(sf::Texture texture);//sets the texture of an object
	sf::Texture GetTexture();//return the texture of an object
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

	Player(b2World* world);//basic constructor, sets just the physics world
	Player(int id, std::string name,int ZOrder,sf::Sprite sprite,b2World*world);//most advanced constructor, sets the id, name, ZOrder(which is the way in which the Objects are rendered,the sprite of the object and the physics world
	void Update(std::map<Input::states, std::string>* keyspressed) override;//uses keyboard input to move the player
};

class Collectable : public Object
{
public:
	Collectable(int id, b2World* world);//basic constructor, sets just the physics world
	Collectable(int id, std::string name,int ZOrder,sf::Sprite sprite,b2World*world);//most advanced constructor, sets the id, name, ZOrder(which is the way in which the Objects are rendered,the sprite of the object and the physics world
	~Collectable();//default destructor
	void Initialize();//sets the "physics parts" for the collectable. this need to be different than the basic one because the collectable acts like a trigger 
	void Update(std::map<Input::states, std::string>* keyspressed) override;//if the player collides with the collectable, the collectable is set as ready to be deleted
};
