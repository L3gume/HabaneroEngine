//
// Created by notjustin on 12/24/17.
//

#include <windows.h>

#include "engine/core/Engine.h"
#include "engine/core/components/CameraComponent.h"
#include "engine/core/components/ScriptComponent.h"
#include "engine/core/ecs/EntityConstructor.h"
#include "engine/core/systems/TransformSystem.h"
#include "engine/core/systems/RenderSystem.h"
#include "engine/core/systems/CameraSystem.h"
#include "engine/core/systems/ScriptSystem.h"
#include "jahbal/renderers/JRenderer.h"
#include "jahbal/components/BillboardComponent.h"
#include "jahbal/components/MeshComponent.h"
#include "jahbal/components/TerrainComponent.h"
#include "jahbal/ShaderManager.h"

using namespace Core;

void Engine::init() {

	m_hAppInst = nullptr;
	m_hMainWnd = nullptr;
	m_Minimized = false;
	m_Maximized = false;
	m_Resizing = false;
	m_ClientWidth = 1280;
	m_ClientHeight = 720;
	m_MainWndCaption = L"Habanero";
	m_Running = true;

	initWindow();
	m_systemManager.addSystem<RenderSystem>(m_ClientWidth, m_ClientHeight,
		m_hMainWnd);
	m_systemManager.addSystem<CameraSystem>();
    ShaderManager::GetInstance()->Init(m_systemManager.getSystem<RenderSystem>()->GetGFXDevice());

	// Manual entity adding for testing, remove once entity serialization system is complete
	Entity& camera = m_entityManager.addEntity("main_camera");
	camera.addComponent<TransformComponent>(Vector3(30.0f, 30.0f, 30.0f), Vector3::Zero, Vector3::One);
	camera.addComponent<CameraComponent>(0.25f * 3.14f, m_ClientWidth, m_ClientHeight,
		1.0f, 1000.0f);

    Entity& sun = m_entityManager.addEntity("sun");
    sun.addComponent<TransformComponent>(Vector3::Zero, Vector3(0.0f, 270.0f, 0.0f), Vector3::One);
    LightComponent& sunLight = sun.addComponent<LightComponent>(LightType::Directional);
    sunLight.m_lightData.Ambient = Vector4(0.1f, 0.1f, 0.1f, 1.0f);
    sunLight.m_lightData.Diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
    sunLight.m_lightData.Specular = Vector4(0.2f, 0.2f, 0.2f, 16.0f);

    Entity& nanosuit = m_entityManager.addEntity("nano_suit");
    nanosuit.addComponent<TransformComponent>(Vector3(10.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3::One);
    nanosuit.addComponent<MeshComponent>("jahbal/resources/nanosuit/nanosuit.obj");

    Entity& billboard = m_entityManager.addEntity("billboard");
    billboard.addComponent<TransformComponent>(Vector3::Zero, Vector3::Zero, Vector3::One);
    billboard.addComponent<BillboardComponent>(15.0f, 15.0f, L"jahbal/resources/textures/tree0.dds");

    Entity& terrain = m_entityManager.addEntity("terrain");
    terrain.addComponent<TransformComponent>(Vector3::Zero, Vector3::Zero, Vector3::One);

    TerrainInfo terrainInfo(L"jahbal/resources/textures/terrain.raw", 2049, 2049, 50, 1);
    terrain.addComponent<TerrainComponent>(terrainInfo);
}

void Engine::gameLoop() {

	MSG msg{0};
	while (m_Running) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// TODO calculate deltaTime and pass it in
			m_systemManager.preUpdate(0);
			m_systemManager.update(0);
		}
	}
}

void Engine::signalRunGame() {
	// TODO
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before m_hMainWnd is valid.
	return Engine::getInstance().MsgProc(hwnd, msg, wParam, lParam);
}

LRESULT Engine::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// handle window messages here

	switch (msg)
	{
	case WM_CLOSE:
	case WM_QUIT:
		m_Running = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_ACTIVATEAPP:
		//Keyboard::ProcessMessage(msg, wParam, lParam);
		//Mouse::ProcessMessage(msg, wParam, lParam);
		break;
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		//Mouse::ProcessMessage(msg, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		//Keyboard::ProcessMessage(msg, wParam, lParam);
		break;
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Engine::initWindow() {
	// boiler-plate win32 api window creation code

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hAppInst;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"D3DWndClassName";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, m_ClientWidth, m_ClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width = R.right - R.left;
	int height = R.bottom - R.top;

	m_hMainWnd = CreateWindowW(L"D3DWndClassName", m_MainWndCaption.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, m_hAppInst, 0);
	if (!m_hMainWnd)
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(m_hMainWnd, SW_SHOW);
	UpdateWindow(m_hMainWnd);

	return true;
}
