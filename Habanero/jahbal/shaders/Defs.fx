#ifndef DEFS_FX
#define DEFS_FX

#define F4_Zero float4(0.0f, 0.0f, 0.0f, 0.0f);

struct Light
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float4 attenuation; // (A0, A1, A2, Pad)
    float4 attributes;  // (Range, Spot, Pad, Pad)
};
struct DirectionalLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 direction;
	float pad;
};

struct PointLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;

	float3 position;
	float range;

	float3 att;
	float pad;
};

struct SpotLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;

	float3 position;
	float range;

	float3 direction;
	float spot;

	float3 att;
	float pad;
};

struct Material
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
};

#endif