#pragma once

#include "engine/core/ecs/component.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

struct LightData
{
public:
    DirectX::Vector4 Ambient;
    DirectX::Vector4 Diffuse;
    DirectX::Vector4 Specular;

    // Packed into 4D vector: (A0, A1, A2, Pad)
    DirectX::Vector4 Attenuation;

    // Packed into 4D vector: (Range, Spot, Pad, Pad)
    DirectX::Vector4 Attributes;
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