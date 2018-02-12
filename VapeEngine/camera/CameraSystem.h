//
// Created by l3gume on 11/02/18.
//

#ifndef VAPEENGINE_CAMERASYSTEM_H
#define VAPEENGINE_CAMERASYSTEM_H

#include <ecs/ecs.h>
#include <glm/matrix.hpp>
#include <components/CameraComponent.h>
#include <components/TransformComponent.h>
#include <core/Engine.h>

using namespace ECS;

class CameraSystem : public System {
    friend class SystemManger;

public:
    CameraSystem() : System() {}

    inline void setActiveCamera(Entity *_cam) noexcept;
    glm::mat4 getMVPFromActiveCamera(glm::mat4 _modelMat);

private:

    void preUpdate(float _deltaTime) override;
    std::vector<Entity *> m_cameras;
    Entity *m_activeCamera = nullptr;

    glm::vec3 cartesianRot;
    glm::vec3 cartesianRight;
    glm::vec3 cartesianUp;
    glm::mat4 viewMat;
    glm::mat4 projMat;
};


#endif //VAPEENGINE_CAMERASYSTEM_H
