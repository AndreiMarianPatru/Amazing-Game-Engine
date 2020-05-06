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
	virtual void UpdateChildren();

	void PrintChildren();
};


class BaseEntity : public Object
{
public:
	/**
	 * static std vector of BaseEntity pointers, currently used to loop all entities for rendering and ticking.
	 */
	static std::vector<BaseEntity*> Renderables;

	sf::Vector2f velocity;


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

	/**
	 * Think is the standard "update" function for all agents
	 * All agents must implement their own Think function - there is nothing provided in the base class.
	 */
	virtual void Think();


	/**
	 * GetSprite provides access to the entities sprite object
	 * @return sf::Sprite current entities sprite
	 */
	sf::Sprite GetSprite() { return sprite; }

	/**
	 * SetColour allows for post-construction alteration of the colour tint
	 * @param colour a sf::Colour value
	 */
	void SetColour(sf::Color colour) { colourTint = colour; }

	/**
	* SetTextureFile is used to set the filename variable
	* @param string a filename
	*/
	void SetTextureFile(std::string file) { filename = file; }

	void m_setposition(float x, float y);


	void Update(std::map<Input::states, std::string>* keyspressed) override;

	void setSprite(sf::Sprite newsprite);
	void m_setshapeb2d();
	void m_setfrictionb2d(float value);
public:
	b2World* world;
	b2Body* body{};

protected:
	std::string filename;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Color colourTint;


protected:
	/**
	 * Initialize assures our texture is loaded using the assigned file name and initial colour tint
	 */
};

class Player : public BaseEntity
{
public:


	Player(b2World* world);
	void Update(std::map<Input::states, std::string>* keyspressed) override;
};
