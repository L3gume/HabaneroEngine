#pragma once

#include <DirectXMath.h>

#include "jahbal/Shader.h"
#include "jahbal/common/Light.h"
#include "jahbal/common/Material.h"
#include "../libraries/DirectXTK/include/SimpleMath.h"

using namespace DirectX;

class JQuadTess : public Shader
{
public:
	JQuadTess(ID3D11Device* device);
	~JQuadTess();

	WORLD_DEC
	WVP_DEC
	EYEPOS_DEC

	/*
	From Shader:

	ID3DX11EffectTechnique* Tech;
	ID3DX11Effect* m_FX;
	ID3D11InputLayout* m_InputLayout;
	ID3D11Device* m_deviceReference;
	*/
};