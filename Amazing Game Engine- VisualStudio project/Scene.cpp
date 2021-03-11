#include "Scene.h"


Scene::Scene(int index): index(index)
{
	this->active = false;
}

void Scene::printNoOfObjects()
{
	std::cout << "number of elements in active scene " << this->objects.size();
}

void Scene::AddObjectToScene(std::shared_ptr<Object> object)
{
	objects.push_back(object);
}

SceneManager::SceneManager()
{
}

void SceneManager::AddScene(Scene* scene)
{
	scenes.push_back(scene);
}

void SceneManager::LoadScene(int index)
{
	std::list<Scene*>::iterator it;
	for (it = scenes.begin(); it != scenes.end(); ++it)
	{
		if ((*it)->index == index)
		{
			std::list<std::shared_ptr<Object>>::iterator it1;

			this->activeObjects.clear();
			///populate the active objects list
			for (it1 = (*it)->objects.begin(); it1 != (*it)->objects.end(); ++it1)
			{
				std::shared_ptr<Object> copy = (*it1);
				activeObjects.push_back(copy);
			}
		}
		else
		{
			(*it)->active = false;
		}
	}
}



