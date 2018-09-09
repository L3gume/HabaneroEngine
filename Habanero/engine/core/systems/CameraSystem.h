//
// Created by l3gume on 11/02/18.
//
#pragma once
#ifndef VAPEENGINE_CAMERASYSTEM_H
#define VAPEENGINE_CAMERASYSTEM_H
#include <d3d11.h>

#include "engine/core/ecs/ecs.h"
#include "engine/core/components/CameraComponent.h"
#include "engine/core/components/TransformComponent.h"
#include "engine/core/Engine.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

using namespace ecs;

class CameraSystem : public System {
    friend class SystemManger;

public:
    CameraSystem() : System() {
#if EDITOR
        m_enabledInEditorMode = true;
#endif
    }

	Entity* getActiveCamera() { return m_activeCamera; }
    inline void setActiveCamera(Entity *_cam) noexcept; // This essentially forces the system to use a specific camera,
                                                        // usually you'd have only one anyway.
    DirectX::SimpleMath::Matrix getMVPFromActiveCamera(DirectX::SimpleMath::Matrix _modelMat);

    DirectX::SimpleMath::Matrix viewMat;
    DirectX::SimpleMath::Matrix projMat;
private:

    void preUpdate(float _deltaTime) override;
	void updateProjectionMatrix();

    Entity *m_activeCamera = nullptr;

};

#endif //VAPEENGINE_CAMERASYSTEM_H
