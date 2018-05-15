#include "../ecs/ecs.h"
#include "Scene.h"

using namespace ECS;

void Scene::AddEntity(Entity* entity)
{
	m_EntityList.push_back(entity);
}

void Scene::Shutdown()
{
	for (Entity* e : m_EntityList)
	{
		//delete e->m_VisualComponent;
	}

	for (Light* l : m_LightList)
	{
		delete l;
	}
}