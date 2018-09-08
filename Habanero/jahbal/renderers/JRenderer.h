#pragma once

#include <d3d11_1.h>
#include <d3d11shader.h>
#include <DirectXMath.h>
#include <vector>

#include "engine/core/ecs/entitymanager.h"
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
	void DrawScene(const std::vector<ecs::Entity*>& renderableEntities, 
        const std::vector<ecs::Entity*>& billboardEntities,
        const std::vector<ecs::Entity*>& terrainEntities,
        const ecs::Entity& activeCamera, const ecs::Entity& sunLight);
	void DrawMeshEntity(const ecs::Entity& entity, const ecs::Entity& cam, const LightComponent& sun);
	void DrawBillboardEntity(const ecs::Entity& entity, const ecs::Entity& cam, const LightComponent& sun);
	void DrawTerrainEntity(const ecs::Entity& entity, const ecs::Entity& cam);

	JRenderer();
	~JRenderer() {}
};
}  // namespace jahbal


