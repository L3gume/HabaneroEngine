//
// Created by l3gume on 11/02/18.
//

#ifndef HABANERO_TRANSFORMCOMPONENT_H
#define HABANERO_TRANSFORMCOMPONENT_H

#include "engine/core/ecs/ecs.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

using DirectX::Vector3;

struct TransformComponent : ECS::Component {
    TransformComponent(Vector3 _pos, Vector3 _rot, Vector3 _scl) : position(_pos), rotation(_rot), scale(_scl) {}

    Vector3 position = Vector3(0.f, 0.f, 0.f);
    Vector3 rotation = Vector3(0.f, 0.f, 0.f);
    Vector3 scale = Vector3(1.f, 1.f, 1.f);

    Vector3 abs_position = Vector3(0.f, 0.f, 0.f);
    Vector3 abs_rotation = Vector3(0.f, 0.f, 0.f);
    Vector3 abs_scale = Vector3(1.f, 1.f, 1.f);
};

#endif //HABANERO_TRANSFORMCOMPONENT_H
