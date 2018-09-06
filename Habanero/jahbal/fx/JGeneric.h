#pragma once

#include <DirectXMath.h>

#include "jahbal/Shader.h"
#include "libraries/DirectXTK/include/SimpleMath.h"
#include "jahbal/components/LightComponent.h"
#include "jahbal/common/Material.h"

class JGeneric : public Shader
{
public:
	JGeneric(ID3D11Device* device);
	~JGeneric();

	WVP_DEC
	WORLD_DEC
	WOLRDINV_DEC
	EYEPOS_DEC
    LIGHT_DEC
	MAT_DEC

	DIFFUSE_DEC
	SPEC_DEC

	/*
	From Shader:

	ID3DX11EffectTechnique* Tech;
	ID3DX11Effect* m_FX;
	ID3D11InputLayout* m_InputLayout;
	ID3D11Device* m_deviceReference;
	*/
};