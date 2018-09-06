#include "Defs.fx"
#include "LightFuncs.fx"

cbuffer cbPerFrame
{
	//DirectionalLight gDLight;
	//PointLight gPLight;
    Light gSun;
	float3 gEyePosW;
};

cbuffer cbPerObject
{
	float4x4 gWorldViewProj;
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
};

cbuffer cbPerObject2
{
	Material gMaterial;
};

struct VIN
{
	float3 PosL     : POSITION;
	float3 Normal   : NORMAL;
	float2 TexCoord : TEXCOORD;
};

struct VOUT
{
	float4 PosH      : SV_POSITION;
	float4 PosW      : POSITION;
	float3 NormalW   : NORMAL;
	float2 UV		 : TEXCOORD;
};

SamplerState MeshTextureSampler
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 16;
	AddressU = Wrap;
	AddressV = Wrap;
};

Texture2D gDiffuseMap;
Texture2D gSpecMap;

VOUT VS(VIN vin)
{
	VOUT vout;

	vout.PosW = mul(float4(vin.PosL, 1.0f), gWorld);
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.NormalW = mul(vin.Normal, (float3x3)gWorldInvTranspose);
	vout.UV = vin.TexCoord;

	return vout;
}

// TODO Reimplement lighting
float4 PS(VOUT pin) : SV_Target
{
	float4 mat_d = gDiffuseMap.Sample(MeshTextureSampler, pin.UV);
	float4 mat_s = gSpecMap.Sample(MeshTextureSampler, pin.UV); 
	float4 mat_a = mat_d;
	
	pin.NormalW = normalize(pin.NormalW);
	float3 ptoeye = normalize(gEyePosW - pin.PosW); 

	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 a, d, s;
	computeDirectionalLight(gSun, pin.NormalW, ptoeye, mat_d, mat_s, a, d, s);
	ambient += a;
	diffuse += d;
	spec += s;

    /*
	computePointLight(gPLight, pin.NormalW, pin.PosW, ptoeye, mat_d, mat_s, a, d, s);
	ambient += a;
	diffuse += d;
	spec += s;
    */

	float4 color = ambient + diffuse + spec;
	color.a = gMaterial.ambient.a;

	return color;
}

technique11 Tech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetHullShader(NULL);
		SetDomainShader(NULL);
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
};