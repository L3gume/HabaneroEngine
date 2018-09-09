#pragma once

#include <d3d11.h>

#include "../libraries/DirectXTK/include/SimpleMath.h"

using namespace DirectX;

namespace jahbal {
class Material
{
public:

	Material() {}
	DirectX::SimpleMath::Vector4 Ambient;
	DirectX::SimpleMath::Vector4 Diffuse;
	DirectX::SimpleMath::Vector4 Specular;
};
}  // namespace jahbal

