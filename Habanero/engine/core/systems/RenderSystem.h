//
// Created by msukkai on 05/18/18
//
#pragma once
#ifndef HABANARO_RENDERSYSTEM_H
#define HABANARO_RENDERSYSTEM_H

#include <d3d11.h>
#include <DirectXMath.h>

#include "engine/core/ecs/entitymanager.h"
#include "engine/core/ecs/systemmanager.h"
#include "libraries/DirectXTK/include/SimpleMath.h"
#include "jahbal/renderers/JRenderer.h"
#include "jahbal/util/dxerr.h"

using namespace DirectX;

enum BlendState { BSNOBLEND, BSALPHACOVERAGE, BSNOTARGETWRITE, BSALPHA, BSSIZE };
enum RasterizerState { RSWIREFRAME, RSSOLID, RSSOLIDBACK, RSSIZE };
enum DepthStencilState { DSDEFAULT, DSMARKSTENCIL, DSSTENCILEQUAL, DSSIZE };

class RenderSystem : public ecs::System {
    friend class ecs::SystemManager;
    friend class JRenderer;
public:
    void update(float _deltaTime) override;

    std::vector<ecs::Entity*> m_renderableEntities;

    ID3D11Device* GetGFXDevice() { return m_d3dDevice; }
    ID3D11DeviceContext* GetGFXDeviceContext() { return m_d3dImmediateContext; }

    ID3D11RenderTargetView* m_renderTargetView;
    ID3D11DepthStencilView* m_depthStencilView;
    IDXGISwapChain* m_swapChain;
    const Vector4 m_ClearColor = { 0.2f, 0.2f, 0.2f, 1.0f };

    Matrix m_ProjectionMatrix;
    Matrix m_ViewMatrix;

    std::vector<ID3D11RasterizerState*> m_rasterizerStates;
    std::vector<ID3D11BlendState*> m_blendStates;
    std::vector<ID3D11DepthStencilState*> m_depthStencilStates;

private:
    RenderSystem(int width, int height, HWND hMainWnd);
    ~RenderSystem();

    bool InitDX11(HWND hMainWnd);
    void InitRasterizerStates();
    void InitBlendStates();
    void InitDepthStencilStates();
    void OnResize();

	::jahbal::JRenderer m_renderer;

    ID3D11Device* m_d3dDevice;
    ID3D11DeviceContext* m_d3dImmediateContext;
    ID3D11Texture2D* m_depthStencilBuffer;
    D3D11_VIEWPORT m_screenViewport;


    int m_ClientWidth;
    int m_ClientHeight;
    bool m_Enable4xMSAA;


    UINT m_4xMsaaQuality;
};
#endif //HABANARO_RENDERSYSTEM_H
