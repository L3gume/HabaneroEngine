#pragma once

#include "engine/core/ecs/component.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

struct LightData
{
public:
    DirectX::SimpleMath::Vector4 Ambient;
    DirectX::SimpleMath::Vector4 Diffuse;
    DirectX::SimpleMath::Vector4 Specular;
    
    // Packed into 4D vector: (direction.x, direction.y, direction.z, Range)
    DirectX::SimpleMath::Vector4 Direction;

    // Packed into 4D vector: (A0, A1, A2, Spot)
    DirectX::SimpleMath::Vector4 Attenuation;
};

enum LightType
{
    Directional = 0,
    Point = 1,
    Spot = 2
};

struct LightComponent : public ecs::Component
{
    LightComponent(LightType lightType) : m_lightType(lightType) {}

    LightType m_lightType;
    LightData m_lightData;
};