//
// Created by l3gume on 11/02/18.
//

#ifndef HABANERO_TRANSFORMCOMPONENT_H
#define HABANERO_TRANSFORMCOMPONENT_H

#include <d3d11.h>

#include "engine/core/ecs/component.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

struct TransformComponent : ecs::Component {
    TransformComponent(DirectX::Vector3 _pos, DirectX::Vector3 _rot, DirectX::Vector3 _scl) : position(_pos), rotation(_rot), scale(_scl) {}

    DirectX::Vector3 position = DirectX::Vector3(0.f, 0.f, 0.f);
    DirectX::Vector3 rotation = DirectX::Vector3(0.f, 0.f, 0.f);
    DirectX::Vector3 scale = DirectX::Vector3(1.f, 1.f, 1.f);

    DirectX::Vector3 abs_position = DirectX::Vector3(0.f, 0.f, 0.f);
    DirectX::Vector3 abs_rotation = DirectX::Vector3(0.f, 0.f, 0.f);
    DirectX::Vector3 abs_scale = DirectX::Vector3(1.f, 1.f, 1.f);
};

#endif //HABANERO_TRANSFORMCOMPONENT_H
