#pragma once

#include <d3d11_1.h>
#include <d3d11shader.h>
#include <DirectXMath.h>
#include <vector>

#include "engine/core/ecs/ecs.h"
#include "engine/core/Scene.h"
#include "engine/core/components/CameraComponent.h"
#include "libraries/DirectXTK/include/SimpleMath.h"
#include "jahbal/components/LightComponent.h"
#include "jahbal/util/dxerr.h"

class RenderSystem;

namespace jahbal {
class JRenderer
{
public:
	friend class RenderSystem;
private:
	void DrawScene(const std::vector<ECS::Entity*>& renderableEntities, 
        const ECS::Entity& activeCamera, const ECS::Entity& sunLight);
	void DrawMeshEntity(const ECS::Entity& entity, const ECS::Entity& cam, const LightComponent& sun);
	void DrawBillboardEntity(const ECS::Entity& entity, const CameraComponent& cam, const LightComponent& sun);
	void DrawTerrainEntity(const ECS::Entity& entity, const CameraComponent& cam);

	JRenderer();
	~JRenderer() {}
};
}  // namespace jahbal


