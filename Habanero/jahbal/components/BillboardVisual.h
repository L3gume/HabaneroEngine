#pragma once
#include <DirectXMath.h>
#include <d3d11.h>

#include "libraries/DirectXTK/include/SimpleMath.h"
#include "engine/core/ecs/ecs.h"
#include "engine/core/components/VisualComponent.h"

using namespace DirectX;

class JRenderer;

struct BillBoardVertex
{
	BillBoardVertex(float px, float py, float pz, float sx, float sy)
		: position(px, py, pz), size(sx, sy) {}
	BillBoardVertex(Vector3 pos, float sx, float sy)
		: position(pos), size(sx, sy) {}
	BillBoardVertex() : position(0.0f, 0.0f, 0.0f), size(2.0f, 2.0f) {}

	Vector3 position;
	Vector2 size;
};

class BillboardVisual : public ECS::Component
{
public:
	BillboardVisual(ECS::Entity* owner, JRenderer* renderer, float sx, float sy);
	~BillboardVisual();

	//void SetupBuffers();

	BillBoardVertex m_vertex;
	ID3D11Buffer* m_VB;
	ID3D11ShaderResourceView* m_diffuseSRV;
	ID3D11ShaderResourceView* m_specSRV;
};
