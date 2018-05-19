#include <d3d11_1.h>
#include <d3d11shader.h>
#include <stdlib.h>
#include <assert.h>
#include <DirectXMath.h>
#include <vector>
#include <windows.h>

#include "engine/core/Scene.h"
#include "engine/core/ecs/ecs.h"
#include "engine/core/components/VisualComponent.h"
#include "engine/core/systems/RenderSystem.h"
#include "jahbal/components/MeshVisual.h"
#include "jahbal/components/BillboardVisual.h"
#include "jahbal/components/TerrainVisual.h"
#include "jahbal/renderers/JRenderer.h"
#include "jahbal/common/Material.h"
#include "jahbal/Shader.h"
#include "jahbal/Mesh.h"
#include "jahbal/SubMesh.h"
#include "jahbal/common/Camera.h" 
#include "jahbal/ShaderManager.h"
#include "jahbal/fx/JGeneric.h"
#include "jahbal/fx/JBillboard.h"
#include "jahbal/fx/JQuadTess.h"
#include "jahbal/fx/JTerrain.h"
#include "jahbal/common/Light.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

using namespace DirectX;

void JRenderer::DrawScene(Scene* scene)
{
	ID3D11DeviceContext* dc = m_renderSystem->GetGFXDeviceContext();

	dc->ClearRenderTargetView(m_renderSystem->m_renderTargetView, reinterpret_cast<const float*>(&m_renderSystem->m_ClearColor));
	dc->ClearDepthStencilView(m_renderSystem->m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	/*
	Camera* cam = scene->GetActiveCamera();
	Vector3 eyePos = Vector3(cam->m_position);
	Light* sun = nullptr;
	Light* point = nullptr;
	sun = scene->GetLightList()->at(0);
	if (scene->GetLightList()->size() >= 2)
	{
		point = scene->GetLightList()->at(1);
	}

	for (unsigned int i = 0; i < scene->GetEntityList()->size(); i++)
	{
		ECS::Entity* entity = scene->GetEntityList()->at(i);
		VisualComponent* visualComponent = &(entity->getComponent<VisualComponent>());
		
		if (visualComponent->m_visualType == VisualType::MESH) DrawMeshEntity(entity, cam, sun, point);
		else if (visualComponent->m_visualType == VisualType::BILLBOARD) DrawBillboardEntity(entity, cam, sun, point);
		else if (visualComponent->m_visualType == VisualType::TERRAIN) DrawTerrainEntity(entity, cam);
	}

	*/
	HR(m_renderSystem->m_swapChain->Present(0, 0));
}

void JRenderer::DrawMeshEntity(ECS::Entity* entity, Camera* cam, Light* sun, Light* point)
{
	/*
	ID3D11DeviceContext* dc = GetGFXDeviceContext();
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Vector3 eyePos = Vector3(cam->m_position);

	dc->IASetInputLayout(ShaderManager::GetInstance()->m_JGeneric->m_InputLayout);
	ShaderManager::GetInstance()->m_JGeneric->SetDLight((DLightData*)sun->m_LightData);
	ShaderManager::GetInstance()->m_JGeneric->SetPLight((PLightData*)point->m_LightData);

	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f }; // only used with D3D11_BLEND_BLEND_FACTOR
	dc->RSSetState(m_rasterizerStates[RSWIREFRAME]);
	dc->OMSetBlendState(m_blendStates[BSNOBLEND], blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(m_depthStencilStates[DSDEFAULT], 0);

	ID3DX11EffectTechnique* activeTech = ShaderManager::GetInstance()->m_JGeneric->Tech;
	D3DX11_TECHNIQUE_DESC techDesc;
	activeTech->GetDesc(&techDesc);
	for (unsigned int p = 0; p < techDesc.Passes; p++)
	{
		Matrix rotation = Matrix::CreateFromYawPitchRoll(entity->m_rotationEuler.x, entity->m_rotationEuler.y, entity->m_rotationEuler.z);
		Matrix model = rotation * Matrix::CreateTranslation(entity->m_position);
		Matrix modelInvTranspose = model; modelInvTranspose.Invert().Transpose();
		Matrix view = cam->GetLookAtMatrix();
		Matrix MVP = model * view * m_ProjectionMatrix;

		ShaderManager::GetInstance()->m_JGeneric->SetWorldViewProj(MVP);
		ShaderManager::GetInstance()->m_JGeneric->SetWorld(model);
		ShaderManager::GetInstance()->m_JGeneric->SetWorldInvTranspose(modelInvTranspose);
		ShaderManager::GetInstance()->m_JGeneric->SetMaterial(entity->m_VisualComponent->m_Material);
		ShaderManager::GetInstance()->m_JGeneric->SetEyePosW(eyePos);

		MeshVisual* meshVisual = (MeshVisual*)entity->m_VisualComponent;
		Mesh* mesh = meshVisual->m_Mesh;
		for (unsigned int s = 0; s < mesh->m_subMeshList.size(); s++)
		{
			SubMesh* subMesh = &mesh->m_subMeshList[s];

			UINT stride = sizeof(MeshVertex);
			UINT offset = 0;
			GetGFXDeviceContext()->IASetVertexBuffers(0, 1, &subMesh->m_VB, &stride, &offset);
			GetGFXDeviceContext()->IASetIndexBuffer(subMesh->m_IB, DXGI_FORMAT_R32_UINT, 0);

			ShaderManager::GetInstance()->m_JGeneric->SetDiffuseMap(subMesh->m_diffuseSRV);
			ShaderManager::GetInstance()->m_JGeneric->SetSpecMap(subMesh->m_specSRV);

			activeTech->GetPassByIndex(p)->Apply(0, GetGFXDeviceContext());
			GetGFXDeviceContext()->DrawIndexed(subMesh->m_indexList.size(), 0, 0);
		}
	}

	dc->RSSetState(0);
	dc->OMSetBlendState(0, blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(0, 0);
	*/
}

void JRenderer::DrawBillboardEntity(ECS::Entity* entity, Camera* cam, Light* sun, Light* point)
{
	/*
	ID3D11DeviceContext* dc = GetGFXDeviceContext();
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	Vector3 eyePos = Vector3(cam->m_position);

	dc->IASetInputLayout(ShaderManager::GetInstance()->m_JBillboard->m_InputLayout);
	ShaderManager::GetInstance()->m_JBillboard->SetDLight((DLightData*)sun->m_LightData);
	ShaderManager::GetInstance()->m_JBillboard->SetPLight((PLightData*)point->m_LightData);

	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f }; // only used with D3D11_BLEND_BLEND_FACTOR
	dc->RSSetState(m_rasterizerStates[RSSOLID]);
	dc->OMSetBlendState(m_blendStates[BSALPHACOVERAGE], blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(m_depthStencilStates[DSDEFAULT], 0);

	ID3DX11EffectTechnique* activeTech = ShaderManager::GetInstance()->m_JBillboard->Tech;
	D3DX11_TECHNIQUE_DESC techDesc;
	activeTech->GetDesc(&techDesc);
	for (unsigned int p = 0; p < techDesc.Passes; p++)
	{
		Matrix view = cam->GetLookAtMatrix();
		Matrix VP = view * m_ProjectionMatrix;

		ShaderManager::GetInstance()->m_JBillboard->SetViewProj(VP);
		ShaderManager::GetInstance()->m_JBillboard->SetMaterial(entity->m_VisualComponent->m_Material);
		ShaderManager::GetInstance()->m_JBillboard->SetEyePosW(eyePos);

		BillboardVisual* boardVisual = (BillboardVisual*)entity->m_VisualComponent;

		UINT stride = sizeof(BillBoardVertex);
		UINT offset = 0;
		GetGFXDeviceContext()->IASetVertexBuffers(0, 1, &boardVisual->m_VB, &stride, &offset);

		ShaderManager::GetInstance()->m_JBillboard->SetDiffuseMap(boardVisual->m_diffuseSRV);

		activeTech->GetPassByIndex(p)->Apply(0, GetGFXDeviceContext());
		GetGFXDeviceContext()->Draw(1, 0);
	}

	dc->RSSetState(0);
	dc->OMSetBlendState(0, blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(0, 0);
	*/
}

void JRenderer::DrawTerrainEntity(ECS::Entity* entity, Camera* cam)
{
	/*
	ID3D11DeviceContext* dc = GetGFXDeviceContext();
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	dc->IASetInputLayout(ShaderManager::GetInstance()->m_JTerrain->m_InputLayout);

	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f }; // only used with D3D11_BLEND_BLEND_FACTOR
	dc->RSSetState(m_rasterizerStates[RSWIREFRAME]);
	dc->OMSetBlendState(m_blendStates[BSNOBLEND], blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(m_depthStencilStates[DSDEFAULT], 0);

	TerrainVisual* terrainVisual = (TerrainVisual*)entity->m_VisualComponent;
	
	UINT stride = sizeof(TerrainVertex);
	UINT offset = 0;
	GetGFXDeviceContext()->IASetVertexBuffers(0, 1, &terrainVisual->m_VB, &stride, &offset);
	GetGFXDeviceContext()->IASetIndexBuffer(terrainVisual->m_IB, DXGI_FORMAT_R16_UINT, 0);

	Vector3 eyePos = Vector3(cam->m_position);
	Matrix view = cam->GetLookAtMatrix();
	Matrix VP = view * m_ProjectionMatrix;

	ShaderManager::GetInstance()->m_JTerrain->SetEyePosW(eyePos);
	ShaderManager::GetInstance()->m_JTerrain->SetViewProj(VP);

	ShaderManager::GetInstance()->m_JTerrain->SetHeightMap(terrainVisual->m_heightMapSRV);
	ShaderManager::GetInstance()->m_JTerrain->SetTessParams(Vector4(0, 1000, 0, 6));

	ID3DX11EffectTechnique* activeTech = ShaderManager::GetInstance()->m_JTerrain->Tech;
	D3DX11_TECHNIQUE_DESC techDesc;
	activeTech->GetDesc(&techDesc);
	for (unsigned int p = 0; p < techDesc.Passes; p++)
	{
		activeTech->GetPassByIndex(p)->Apply(0, GetGFXDeviceContext());
		GetGFXDeviceContext()->DrawIndexed(terrainVisual->m_numPatchQuadFaces * 4, 0, 0);
	}

	dc->RSSetState(0);
	dc->OMSetBlendState(0, blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(0, 0);
	*/
}

