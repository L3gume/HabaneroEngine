#pragma once

#include "jahbal/Shader.h"
#include "../libraries/DirectXTK/include/SimpleMath.h"

using namespace DirectX;

class JTerrain : public Shader
{
public:
	JTerrain(ID3D11Device* device);
	~JTerrain();

	VP_DEC
	EYEPOS_DEC
	TPARAMS_DEC

	HMAP_DEC
};