//
// Created by msukkai on 05/18/18
//
#pragma once
#ifndef HABANARO_RENDERSYSTEM_H
#define HABANARO_RENDERSYSTEM_H

#include <d3d11.h>
#include <DirectXMath.h>

#include "jahbal/util/dxerr.h"
#include "libraries/DirectXTK/include/SimpleMath.h"
#include "engine/core/ecs/ecs.h"

using namespace DirectX;

enum BlendState { BSNOBLEND, BSALPHACOVERAGE, BSNOTARGETWRITE, BSALPHA, BSSIZE };
enum RasterizerState { RSWIREFRAME, RSSOLID, RSSOLIDBACK, RSSIZE };
enum DepthStencilState { DSDEFAULT, DSMARKSTENCIL, DSSTENCILEQUAL, DSSIZE };

class RenderSystem : public ECS::System {
    friend class SystemManager;
    friend class JRenderer;
public:

    //void renderEntity(GLuint& v_buf, const Entity* _ent, float _deltaTime);
    void preUpdate(float _deltaTime) override;
    //void update(float _deltaTime) override;

    std::vector<ECS::Entity*> m_renderableEntities;

    ID3D11Device* GetGFXDevice() { return m_d3dDevice; }
    ID3D11DeviceContext* GetGFXDeviceContext() { return m_d3dImmediateContext; }

private:
    RenderSystem(int width, int height, HWND hMainWnd);
    ~RenderSystem();

    bool InitDX11(HWND hMainWnd);
    void InitRasterizerStates();
    void InitBlendStates();
    void InitDepthStencilStates();
    void OnResize();

    ID3D11Device* m_d3dDevice;
    ID3D11DeviceContext* m_d3dImmediateContext;
    IDXGISwapChain* m_swapChain;
    ID3D11Texture2D* m_depthStencilBuffer;
    ID3D11RenderTargetView* m_renderTargetView;
    ID3D11DepthStencilView* m_depthStencilView;
    D3D11_VIEWPORT m_screenViewport;

    Matrix m_ProjectionMatrix;
    Matrix m_ViewMatrix;

    std::vector<ID3D11RasterizerState*> m_rasterizerStates;
    std::vector<ID3D11BlendState*> m_blendStates;
    std::vector<ID3D11DepthStencilState*> m_depthStencilStates;

    int m_ClientWidth;
    int m_ClientHeight;
    bool m_Enable4xMSAA;
    const Vector4 m_ClearColor = { 0.2f, 0.2f, 0.2f, 1.0f };


    UINT m_4xMsaaQuality;
};

// DX Error Checking
#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILEW__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
#endif

#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

#endif //HABANARO_RENDERSYSTEM_H
