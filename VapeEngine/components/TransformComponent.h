//
// Created by l3gume on 11/02/18.
//

#ifndef VAPEENGINE_TRANSFORMCOMPONENT_H
#define VAPEENGINE_TRANSFORMCOMPONENT_H

#include <ecs/ecs.h>
#include <glm/vec3.hpp>

struct TransformComponent : ECS::Component {
    TransformComponent() = default;
    TransformComponent(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl) : position(_pos), rotation(_rot), scale(_scl) {}

    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
};

#endif //VAPEENGINE_TRANSFORMCOMPONENT_H
