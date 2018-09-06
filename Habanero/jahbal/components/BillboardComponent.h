#pragma once
#include <DirectXMath.h>
#include <d3d11.h>

#include "libraries/DirectXTK/include/SimpleMath.h"
#include "libraries/DirectXTK/include/WICTextureLoader.h"
#include "engine/core/Engine.h"
#include "engine/core/ecs/ecs.h"
#include "engine/core/components/VisualComponent.h"
#include "engine/core/systems/RenderSystem.h"
#include "jahbal/renderers/JRenderer.h"
#include "jahbal/util/dxmacros.h"

using namespace DirectX;

// TODO take out position from here since it's going to be in the TransformComponent
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

struct BillboardComponent : public ECS::Component
{
	BillboardComponent(float sx, float sy, std::wstring texture_filename) : 
		m_vertex(Vector3::Zero, sx, sy), m_textureFilename(texture_filename) {
        SetupBuffers(); 
        LoadTexture();
    }
	~BillboardComponent() 
	{
		if (m_diffuseSRV) m_diffuseSRV->Release();
		if (m_specSRV) m_specSRV->Release();
	}

	BillBoardVertex m_vertex;
	ID3D11Buffer* m_VB;
	ID3D11ShaderResourceView* m_diffuseSRV;
	ID3D11ShaderResourceView* m_specSRV;
    std::wstring m_textureFilename;

	void SetupBuffers() {
		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(BillBoardVertex);
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_vertex;
		HR(Core::Engine::getInstance().getSystemManager().
			getSystem<RenderSystem>()->GetGFXDevice()->CreateBuffer(&vbd, &vinitData, &m_VB));
	}

    void LoadTexture() {
        RenderSystem* render_system =
            Core::Engine::getInstance().getSystemManager().getSystem<RenderSystem>();
        ID3D11Resource* texResource = nullptr;
        CreateWICTextureFromFile(
            render_system->GetGFXDevice(),
            render_system->GetGFXDeviceContext(),
            m_textureFilename.c_str(),
            &texResource, &m_diffuseSRV);
        ReleaseCOM(texResource);

        m_specSRV = nullptr;
    }

};
