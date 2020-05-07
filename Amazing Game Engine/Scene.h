#pragma once

#include "entity.h"
#include <list>
class Scene
{
public:
	//static std vector of BaseEntity pointers, currently used to loop all entities for rendering and ticking.
	std::list<Object*> objects;

	void printNoOfObjects();
	
	void AddObjectToScene(Object* object);

	
};

