//
// Created by notjustin on 12/24/17.
//
#pragma once
#ifndef HABANERO_GAMEMANAGER_H
#define HABANERO_GAMEMANAGER_H

#include <windows.h>

#include "engine/core/ecs/entitymanager.h"
#include "engine/core/ecs/systemmanager.h"
#include "engine/core/Scene.h"
#include "libraries/DirectXTK/include/Keyboard.h"

class JRenderer;

namespace Core {

    class Engine {
    public:
        static Engine &getInstance() {
            static Engine instance; // Guaranteed to be destroyed.
            return instance;
        }

        Engine(Engine const &) = delete;
        void operator=(Engine const &) = delete;

        void init(); // will involve starting the systems in the right order
        void gameLoop();
        void shutDown() { m_bShutdown = true; }

        void signalRunGame();

        inline bool isInitialized() const { return m_bInitialized; }
        static inline double getCurTime() { return 0; }

        ecs::EntityManager& getEntityManager() { return m_entityManager; }
        ecs::SystemManager& getSystemManager() { return m_systemManager; }

        int getClientWidth() { return m_ClientWidth; }
        int getClientHeight() { return m_ClientHeight; }
		
		LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    private:
        Engine() = default;

		bool initWindow();

        ecs::EntityManager m_entityManager;
        ecs::SystemManager m_systemManager;
		Scene m_activeScene;

        float m_fCurTime = 0.f;
        float m_fLastTime = 0.f;

        bool m_bInitialized : 1;
        bool m_bShutdown    : 1;

		// win32 window params
		HINSTANCE		m_hAppInst;
		HWND			m_hMainWnd;
		bool			m_Minimized;
		bool			m_Maximized;
		bool			m_Resizing;
		bool			m_Running;
		int				m_ClientWidth;
		int				m_ClientHeight;
		std::wstring	m_MainWndCaption;
#if EDITOR
        bool m_bRunGame      : 1;
#endif
    };

}
#endif //HABANERO_GAMEMANAGER_H
