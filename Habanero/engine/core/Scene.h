#pragma once

#include <vector>

#include "engine/core/ecs/ecs.h"
#include "jahbal/common/Camera.h"
#include "jahbal/common/Light.h"

namespace Core {
class Scene
{
public:
	void AddEntity(ECS::Entity* entity);

	void Shutdown();

	std::vector<ECS::Entity*>* GetEntityList() { return &m_EntityList; }
	std::vector<jahbal::Light*>* GetLightList() { return &m_LightList; }

	void SetActiveCamera(jahbal::Camera* cam) { m_ActiveCamera = cam; }
	jahbal::Camera* GetActiveCamera() { return m_ActiveCamera; }

private:
	std::vector<ECS::Entity*> m_EntityList;
	std::vector<jahbal::Light*> m_LightList;
	jahbal::Camera* m_ActiveCamera;

};
}  // namespace Core
