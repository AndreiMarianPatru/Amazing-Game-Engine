#pragma once

#include "entity.h"
#include <list>

class Scene
{
public:
	///std list of smart pointers<Objects>, currently used to store all Objects used in a scene, this is meant to be changed only if the design of the scene changes.
	std::list<std::shared_ptr<Object>> objects; 
	int index;/// index of the scene, used for loading a specific scene
	bool active;/// is one scene active or not

	Scene(int index);///basic constructor, sets just the index

	void printNoOfObjects();///used for debugging, prints the number of objects in a scene

	void AddObjectToScene(std::shared_ptr<Object> object);///adds a pointer to an object to the list of objects of current scene
};

class SceneManager
{
public:

	std::list<Scene*> scenes;///list of Scenes, currently used for selecting a specific scene after iterating through it 
	std::list<std::shared_ptr<Object>> activeObjects;///a list of pointers<Object> which are active now and need to be displayed, this list is meant to be changed frequently 

	SceneManager();
	void AddScene(Scene* scene);///add a pointer to a scene to the list of scenes
	void LoadScene(int index);///iterate through a list of scenes and if we find the desired one, empty the list of active objects and push in all the objects specific to the desired scene and make it active 

};
