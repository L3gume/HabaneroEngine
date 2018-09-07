//
// Created by l3gume on 11/02/18.
//

#ifndef HABANERO_TRANSFORMCOMPONENT_H
#define HABANERO_TRANSFORMCOMPONENT_H

#include "engine/core/ecs/component.h"
#include "glm/vec3.hpp"
#include "libraries/visit_struct/visit_struct.hpp"
#include "d3d11.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

struct TransformComponent : ecs::Component {
    TransformComponent(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scl) : position(_pos), rotation(_rot), scale(_scl) {}

    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
    
	DirectX::Vector3 vposition = DirectX::Vector3::Zero;
    DirectX::Vector3 vrotation = DirectX::Vector3::Zero;
    DirectX::Vector3 vscale = DirectX::Vector3(1.f);

    glm::vec3 abs_position = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 abs_rotation = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 abs_scale = glm::vec3(1.f, 1.f, 1.f);
};

VISITABLE_STRUCT(TransformComponent, vposition, vrotation, vscale);

#endif //HABANERO_TRANSFORMCOMPONENT_H
