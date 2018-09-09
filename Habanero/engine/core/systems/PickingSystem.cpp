#include "engine/core/systems/PickingSystem.h"

#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <iostream>

#include "engine/core/ecs/ecs.h"
#include "engine/core/ecs/entitymanager.h"
#include "engine/core/ecs/system.h"
#include "engine/core/Engine.h"
#include "engine/core/systems/CameraSystem.h"
#include "engine/core/input/InputManager.h"
#include "engine/core/input/InputMessage.h"
#include "jahbal/Mesh.h"
#include "jahbal/components/MeshComponent.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

using DirectX::SimpleMath::Ray;
using DirectX::SimpleMath::Vector2;
using DirectX::SimpleMath::Vector3;
using DirectX::SimpleMath::Vector4;
using DirectX::SimpleMath::Matrix;

void PickingSystem::onMousePressed(const input::MouseClickedInputMessage& _msMsg)  {
    if (_msMsg.MOUSE_BUTTON_1) {
        const auto& mouseState = input::InputManager::getInstance().getMouseState();
        pick(mouseState.x, mouseState.y);
    }
}

void PickingSystem::pick(int screenX, int screenY) {
    float screenWidth = Core::Engine::getInstance().getClientWidth();
    float screenHeight = Core::Engine::getInstance().getClientHeight();
    CameraSystem* camSystem = Core::Engine::getInstance().
        getSystemManager().getSystem<CameraSystem>();
    assert(camSystem);

    // normalize device coordinates x:[-1,1] y:[-1,1]
    DirectX::SimpleMath::Vector2 ndc = DirectX::SimpleMath::Vector2(
        ((float(screenX) / screenWidth) - 0.5f) * 2.0f,
        ((float(screenY) / screenHeight) - 0.5f) * -2.0f);

    // transform ray from screen space to view space
    Ray ray(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
        DirectX::SimpleMath::Vector3(ndc.x / camSystem->projMat.m[0][0],
            ndc.y / camSystem->projMat.m[1][1], 1.0f));

    // transform ray from view space to world space
    DirectX::SimpleMath::Matrix invView = camSystem->viewMat.Invert();
    DirectX::SimpleMath::Vector3::Transform(ray.position, invView, ray.position);
    DirectX::SimpleMath::Vector3::TransformNormal(ray.direction, invView, ray.direction);
    ray.direction.Normalize();

    const auto& meshEntities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
        getComponentTypeID<MeshComponent>());
    // TODO implement ray interestection logic
    for (auto entity : meshEntities) {
        Mesh* mesh = entity->getComponent<MeshComponent>().m_Mesh.get();
        BoundingBox meshBox;

        std::vector<DirectX::XMFLOAT3> points;
        for (const auto& vertex : mesh->m_vertexList) {
            points.push_back(DirectX::XMFLOAT3(vertex.position.x, vertex.position.y,
                vertex.position.z));
        }

        DirectX::BoundingBox::CreateFromPoints(meshBox, points.size(),
            &points[0], sizeof(DirectX::XMFLOAT3));

        float distance;
        if (ray.Intersects(meshBox, distance)) {
            std::cout << "test" << std::endl;
        }
    }
}