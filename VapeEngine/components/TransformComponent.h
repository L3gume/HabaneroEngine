//
// Created by l3gume on 11/02/18.
//

#ifndef VAPEENGINE_TRANSFORMCOMPONENT_H
#define VAPEENGINE_TRANSFORMCOMPONENT_H

#include <ecs/ecs.h>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

struct TransformComponent : ECS::Component {
    TransformComponent(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl) : position(_pos), rotation(_rot), scale(_scl) {}

    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);

    glm::vec3 abs_position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 abs_rotation = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 abs_scale = glm::vec3(1.f, 1.f, 1.f);

    inline glm::vec3 forward() const {
        glm::mat4 rot(glm::toMat4(glm::quat(abs_rotation)));
        return rot[2];
    }

    inline glm::vec3 up() const {
        glm::mat4 rot(glm::toMat4(glm::quat(abs_rotation)));
        return rot[1];
    }

    inline glm::vec3 right() const {
        glm::mat4 rot(glm::toMat4(glm::quat(abs_rotation)));
        return rot[0];
    }

    inline glm::vec3 local_forward() const {
        glm::mat4 rot(glm::toMat4(glm::quat(rotation)));
        return rot[2];
    }

    inline glm::vec3 local_up() const {
        glm::mat4 rot(glm::toMat4(glm::quat(rotation)));
        return rot[1];
    }

    inline glm::vec3 local_right() const {
        glm::mat4 rot(glm::toMat4(glm::quat(rotation)));
        return rot[0];
    }
};

#endif //VAPEENGINE_TRANSFORMCOMPONENT_H
