#pragma once

#include <d3d11_1.h>
#include <d3d11shader.h>
#include <DirectXMath.h>
#include <vector>

#include "engine/core/ecs/ecs.h"
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
	RenderSystem* m_renderSystem;
	
	void DrawScene(Core::Scene* scene);
	void DrawMeshEntity(ECS::Entity* entity, Camera* cam, Light* sun, Light* point);
	void DrawBillboardEntity(ECS::Entity* entity, Camera* cam, Light* sun, Light* point);
	void DrawTerrainEntity(ECS::Entity* entity, Camera* cam);

	JRenderer(RenderSystem* render_system) : m_renderSystem(render_system) {}
	~JRenderer() {}
};
}  // namespace jahbal


