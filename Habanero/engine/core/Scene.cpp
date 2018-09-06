#include "Scene.h"

#include "engine/core/ecs/ecs.h"
#include "jahbal/common/Light.h"

using namespace ecs;

namespace Core {
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

	for (jahbal::Light* l : m_LightList)
	{
		delete l;
	}
}
}