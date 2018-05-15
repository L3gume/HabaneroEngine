#pragma once

#include <d3d11.h>

#include "../libraries/DirectXTK/include/SimpleMath.h"

using namespace DirectX;

class Material
{
public:

	Material() {}
	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
};

