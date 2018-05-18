#pragma once

#include <vector>

#include "engine/core/ecs/ecs.h"

class ECS::Entity;
class Light;
class Camera;

class Scene
{
public:
	void AddEntity(ECS::Entity* entity);

	void Shutdown();

	std::vector<ECS::Entity*>* GetEntityList() { return &m_EntityList; }
	std::vector<Light*>* GetLightList() { return &m_LightList; }

	void SetActiveCamera(Camera* cam) { m_ActiveCamera = cam; }
	Camera* GetActiveCamera() { return m_ActiveCamera; }

private:
	std::vector<ECS::Entity*> m_EntityList;
	std::vector<Light*> m_LightList;
	Camera* m_ActiveCamera;

};
