#pragma once

#include <d3d11_1.h>
#include <d3d11shader.h>
#include <DirectXMath.h>
#include <vector>

#include "engine/core/ecs/entitymanager.h"
#include "engine/core/Scene.h"
#include "libraries/DirectXTK/include/SimpleMath.h"
#include "jahbal/common/Camera.h"
#include "jahbal/util/dxerr.h"

class RenderSystem;

namespace jahbal {
class JRenderer
{
public:
	friend class RenderSystem;
private:
	void DrawScene(const std::vector<ecs::Entity*>& renderableEntities, 
		           ecs::Entity* activeCamera);
	void DrawMeshEntity(const ecs::Entity& entity, const Camera& cam, const Light& sun, const Light& point);
	void DrawBillboardEntity(const ecs::Entity& entity, const Camera& cam, const Light& sun, const Light& point);
	void DrawTerrainEntity(const ecs::Entity& entity, const Camera& cam);

	JRenderer();
	~JRenderer() {}
};
}  // namespace jahbal


