#pragma once

#include <d3d11_1.h>
#include <d3d11shader.h>
#include <DirectXMath.h>
#include <vector>

#include "jahbal/util/dxerr.h"
#include "engine/core/ecs/ecs.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

using namespace DirectX;

class Scene;
class Camera;
class Entity;
class Light;
class RenderSystem;

class JRenderer
{
    friend RenderSystem;

private:
    void DrawScene(Scene* scene);
    void DrawMeshEntity(ECS::Entity* entity, Camera* cam, Light* sun, Light* point);
    void DrawBillboardEntity(ECS::Entity* entity, Camera* cam, Light* sun, Light* point);
    void DrawTerrainEntity(ECS::Entity* entity, Camera* cam);

    JRenderer() {};
    ~JRenderer() {};
    RenderSystem* m_renderSystem;
};


