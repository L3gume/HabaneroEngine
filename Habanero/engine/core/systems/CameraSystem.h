//
// Created by l3gume on 11/02/18.
//
#pragma once
#ifndef VAPEENGINE_CAMERASYSTEM_H
#define VAPEENGINE_CAMERASYSTEM_H

#include "engine/core/ecs/ecs.h"
#include "engine/core/components/CameraComponent.h"
#include "engine/core/components/TransformComponent.h"
#include "engine/core/Engine.h"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace ECS;

class CameraSystem : public System {
    friend class SystemManger;

public:
    CameraSystem() : System() {
#if EDITOR
        m_enabledInEditorMode = true;
#endif
    }

    inline void setActiveCamera(Entity *_cam) noexcept; // This essentially forces the system to use a specific camera,
                                                        // usually you'd have only one anyway.
    glm::mat4 getMVPFromActiveCamera(glm::mat4 _modelMat);

private:

    void preUpdate(float _deltaTime) override;
    Entity *m_activeCamera = nullptr;

    glm::vec3 cartesianRot;
    glm::vec3 cartesianRight;
    glm::vec3 cartesianUp;
    glm::mat4 viewMat;
    glm::mat4 projMat;
};

#endif //VAPEENGINE_CAMERASYSTEM_H
