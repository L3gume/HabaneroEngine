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
	void DrawScene(const Core::Scene& scene);
	void DrawMeshEntity(const ECS::Entity& entity, const Camera& cam, const Light& sun, const Light& point);
	void DrawBillboardEntity(const ECS::Entity& entity, const Camera& cam, const Light& sun, const Light& point);
	void DrawTerrainEntity(const ECS::Entity& entity, const Camera& cam);

	JRenderer();
	~JRenderer() {}
};
}  // namespace jahbal


