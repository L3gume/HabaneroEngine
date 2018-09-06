#include <d3d11_1.h>
#include <d3d11shader.h>
#include <stdlib.h>
#include <assert.h>
#include <DirectXMath.h>
#include <vector>
#include <windows.h>

#include "engine/core/Scene.h"
#include "engine/core/Engine.h"
#include "engine/core/ecs/ecs.h"
#include "engine/core/components/CameraComponent.h"
#include "engine/core/components/TransformComponent.h"
#include "engine/core/systems/CameraSystem.h"
#include "engine/core/systems/RenderSystem.h"
#include "jahbal/components/MeshComponent.h"
#include "jahbal/components/BillboardComponent.h"
#include "jahbal/components/LightComponent.h"
#include "jahbal/components/TerrainComponent.h"
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
#include "jahbal/util/dxmacros.h"
#include "libraries/DirectXTK/include/SimpleMath.h"

using namespace DirectX;

namespace jahbal {

JRenderer::JRenderer() {}

void JRenderer::DrawScene(const std::vector<ECS::Entity*>& renderableEntities,
                          const std::vector<ECS::Entity*>& billboardEntities,
                          const std::vector<ECS::Entity*>& terrainEntities,
						  const ECS::Entity& activeCamera,
                          const ECS::Entity& sunLight)
{
    assert(activeCamera.hasComponent<CameraComponent>());
    const auto& camera = activeCamera.getComponent<CameraComponent>();

    assert(sunLight.hasComponent<LightComponent>());
    const auto& sun = sunLight.getComponent<LightComponent>();
    assert(sun.m_lightType == LightType::Directional);

	RenderSystem* render_system = Core::Engine::getInstance().getSystemManager().getSystem<RenderSystem>();
	ID3D11DeviceContext* dc = render_system->GetGFXDeviceContext();

	dc->ClearRenderTargetView(render_system->m_renderTargetView, reinterpret_cast<const float*>(&render_system->m_ClearColor));
	dc->ClearDepthStencilView(render_system->m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    for (ECS::Entity* entity : renderableEntities) {
        DrawMeshEntity(*entity, activeCamera, sun);
    }

    for (ECS::Entity* entity : billboardEntities) {
        DrawBillboardEntity(*entity, activeCamera, sun);
    }

    for (ECS::Entity* entity : terrainEntities) {
        DrawTerrainEntity(*entity, activeCamera);
    }

	/*
	const Camera& cam = scene.GetActiveCamera();
	const Vector3& eyePos = Vector3(cam.m_position);
	const Light& sun = nullptr;
	const Light& point = nullptr;
	sun = *(scene.GetLightList()->at(0));
	if (scene.GetLightList()->size() >= 2)
	{
		point = scene.GetLightList()->at(1);
	}

	for (unsigned int i = 0; i < scene.GetEntityList()->size(); i++)
	{
		ECS::Entity* entity = scene.GetEntityList()->at(i);
		VisualComponent* visualComponent = &(entity->getComponent<VisualComponent>());

		if (visualComponent->m_visualType == VisualType::MESH) DrawMeshEntity(entity, cam, sun, point);
		else if (visualComponent->m_visualType == VisualType::BILLBOARD) DrawBillboardEntity(entity, cam, sun, point);
		else if (visualComponent->m_visualType == VisualType::TERRAIN) DrawTerrainEntity(entity, cam);
	}

	*/
	HR(render_system->m_swapChain->Present(0, 0));
}

void JRenderer::DrawMeshEntity(const ECS::Entity& entity, const ECS::Entity& cam, const LightComponent& sun)
{
    CameraSystem* camera_system = Core::Engine::getInstance().getSystemManager().getSystem<CameraSystem>();
    RenderSystem* render_system = Core::Engine::getInstance().getSystemManager().getSystem<RenderSystem>();
    ID3D11DeviceContext* dc = render_system->GetGFXDeviceContext();

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Vector3 eyePos = cam.getComponent<TransformComponent>().position;

	dc->IASetInputLayout(ShaderManager::GetInstance()->m_JGeneric->m_InputLayout);
	ShaderManager::GetInstance()->m_JGeneric->SetLight((LightData*)&sun.m_lightData);

	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f }; // only used with D3D11_BLEND_BLEND_FACTOR
	dc->RSSetState(render_system->m_rasterizerStates[RSSOLID]);
	dc->OMSetBlendState(render_system->m_blendStates[BSNOBLEND], blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(render_system->m_depthStencilStates[DSDEFAULT], 0);

	ID3DX11EffectTechnique* activeTech = ShaderManager::GetInstance()->m_JGeneric->Tech;
	D3DX11_TECHNIQUE_DESC techDesc;
	activeTech->GetDesc(&techDesc);
	for (unsigned int p = 0; p < techDesc.Passes; p++)
	{
        const auto& entityTransform = entity.getComponent<TransformComponent>();
		Matrix rotation = Matrix::CreateFromYawPitchRoll(entityTransform.rotation.x, entityTransform.rotation.y,
            entityTransform.rotation.z);
		Matrix model = rotation * Matrix::CreateTranslation(entityTransform.position);
		Matrix modelInvTranspose = model; modelInvTranspose.Invert().Transpose();
        Matrix view = camera_system->viewMat;
		Matrix MVP = model * view * camera_system->projMat;

		ShaderManager::GetInstance()->m_JGeneric->SetWorldViewProj(MVP);
		ShaderManager::GetInstance()->m_JGeneric->SetWorld(model);
		ShaderManager::GetInstance()->m_JGeneric->SetWorldInvTranspose(modelInvTranspose);
        // TODO Make MaterialComponent
		//ShaderManager::GetInstance()->m_JGeneric->SetMaterial(entity->m_VisualComponent->m_Material);
		ShaderManager::GetInstance()->m_JGeneric->SetEyePosW(eyePos);

        Mesh* mesh = entity.getComponent<MeshComponent>().m_Mesh.get();
		for (unsigned int s = 0; s < mesh->m_subMeshList.size(); s++)
		{
			SubMesh* subMesh = &mesh->m_subMeshList[s];

			UINT stride = sizeof(MeshVertex);
			UINT offset = 0;
			render_system->GetGFXDeviceContext()->IASetVertexBuffers(0, 1, &subMesh->m_VB, &stride, &offset);
			render_system->GetGFXDeviceContext()->IASetIndexBuffer(subMesh->m_IB, DXGI_FORMAT_R32_UINT, 0);

			ShaderManager::GetInstance()->m_JGeneric->SetDiffuseMap(subMesh->m_diffuseSRV);
			ShaderManager::GetInstance()->m_JGeneric->SetSpecMap(subMesh->m_specSRV);

			activeTech->GetPassByIndex(p)->Apply(0, render_system->GetGFXDeviceContext());
			render_system->GetGFXDeviceContext()->DrawIndexed(subMesh->m_indexList.size(), 0, 0);
		}
	}

	dc->RSSetState(0);
	dc->OMSetBlendState(0, blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(0, 0);
}

void JRenderer::DrawBillboardEntity(const ECS::Entity& entity, const ECS::Entity& cam, const LightComponent& sun)
{
    CameraSystem* camera_system = Core::Engine::getInstance().getSystemManager().getSystem<CameraSystem>();
    RenderSystem* render_system = Core::Engine::getInstance().getSystemManager().getSystem<RenderSystem>();
    ID3D11DeviceContext* dc = render_system->GetGFXDeviceContext();

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
    Vector3 eyePos = cam.getComponent<TransformComponent>().position;

	dc->IASetInputLayout(ShaderManager::GetInstance()->m_JBillboard->m_InputLayout);
	//ShaderManager::GetInstance()->m_JBillboard->SetDLight((DLightData*)sun->m_LightData);

	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f }; // only used with D3D11_BLEND_BLEND_FACTOR
	dc->RSSetState(render_system->m_rasterizerStates[RSSOLID]);
	dc->OMSetBlendState(render_system->m_blendStates[BSALPHACOVERAGE], blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(render_system->m_depthStencilStates[DSDEFAULT], 0);

    const auto& billboard = entity.getComponent<BillboardComponent>();
	ID3DX11EffectTechnique* activeTech = ShaderManager::GetInstance()->m_JBillboard->Tech;
	D3DX11_TECHNIQUE_DESC techDesc;
	activeTech->GetDesc(&techDesc);
	for (unsigned int p = 0; p < techDesc.Passes; p++)
	{
        Matrix view = camera_system->viewMat;
		Matrix VP = view * camera_system->projMat;

		ShaderManager::GetInstance()->m_JBillboard->SetViewProj(VP);
		ShaderManager::GetInstance()->m_JBillboard->SetEyePosW(eyePos);


		UINT stride = sizeof(BillBoardVertex);
		UINT offset = 0;
		render_system->GetGFXDeviceContext()->IASetVertexBuffers(0, 1, &billboard.m_VB, &stride, &offset);

		ShaderManager::GetInstance()->m_JBillboard->SetDiffuseMap(billboard.m_diffuseSRV);

		activeTech->GetPassByIndex(p)->Apply(0, render_system->GetGFXDeviceContext());
        render_system->GetGFXDeviceContext()->Draw(1, 0);
	}

	dc->RSSetState(0);
	dc->OMSetBlendState(0, blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(0, 0);
}

void JRenderer::DrawTerrainEntity(const ECS::Entity& entity, const ECS::Entity& cam)
{
    CameraSystem* camera_system = Core::Engine::getInstance().getSystemManager().getSystem<CameraSystem>();
    RenderSystem* render_system = Core::Engine::getInstance().getSystemManager().getSystem<RenderSystem>();
    ID3D11DeviceContext* dc = render_system->GetGFXDeviceContext();

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	dc->IASetInputLayout(ShaderManager::GetInstance()->m_JTerrain->m_InputLayout);

	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f }; // only used with D3D11_BLEND_BLEND_FACTOR
	dc->RSSetState(render_system->m_rasterizerStates[RSWIREFRAME]);
	dc->OMSetBlendState(render_system->m_blendStates[BSNOBLEND], blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(render_system->m_depthStencilStates[DSDEFAULT], 0);

	const TerrainComponent& terrainComponent = entity.getComponent<TerrainComponent>();

	UINT stride = sizeof(TerrainVertex);
	UINT offset = 0;
    render_system->GetGFXDeviceContext()->IASetVertexBuffers(0, 1, &terrainComponent.m_VB, &stride, &offset);
    render_system->GetGFXDeviceContext()->IASetIndexBuffer(terrainComponent.m_IB, DXGI_FORMAT_R16_UINT, 0);

    Vector3 eyePos = cam.getComponent<TransformComponent>().position;
    Matrix view = camera_system->viewMat;
    Matrix VP = view * camera_system->projMat;

	ShaderManager::GetInstance()->m_JTerrain->SetEyePosW(eyePos);
	ShaderManager::GetInstance()->m_JTerrain->SetViewProj(VP);

	ShaderManager::GetInstance()->m_JTerrain->SetHeightMap(terrainComponent.m_heightMapSRV);
	ShaderManager::GetInstance()->m_JTerrain->SetTessParams(Vector4(0, 1000, 0, 6));

	ID3DX11EffectTechnique* activeTech = ShaderManager::GetInstance()->m_JTerrain->Tech;
	D3DX11_TECHNIQUE_DESC techDesc;
	activeTech->GetDesc(&techDesc);
	for (unsigned int p = 0; p < techDesc.Passes; p++)
	{
		activeTech->GetPassByIndex(p)->Apply(0, render_system->GetGFXDeviceContext());
		render_system->GetGFXDeviceContext()->DrawIndexed(terrainComponent.m_numPatchQuadFaces * 4, 0, 0);
	}

	dc->RSSetState(0);
	dc->OMSetBlendState(0, blendFactors, 0xffffffff);
	dc->OMSetDepthStencilState(0, 0);
}

}  // namespace jahbal

