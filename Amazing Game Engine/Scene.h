#pragma once

#include "entity.h"
#include <list>

class Scene
{
public:
	//static std vector of BaseEntity pointers, currently used to loop all entities for rendering and ticking.
	std::list<std::shared_ptr<Object>> objects;
	int index;
	bool active;

	Scene(int index);

	void printNoOfObjects();

	void AddObjectToScene(std::shared_ptr<Object> object);
};

class SceneManager
{
public:

	std::list<Scene*> scenes;
	std::list<std::shared_ptr<Object>> activeObjects;

	SceneManager();
	void AddScene(Scene* scene);
	void LoadScene(int index);
};
