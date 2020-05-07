#include "Scene.h"

void Scene::printNoOfObjects()
{
	std::cout<<"number of elements in active scene "<<this->objects.size();
}

void Scene::AddObjectToScene(Object* object)
{
	objects.push_back(object);
}
