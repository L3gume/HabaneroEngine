//
// Created by notjustin on 12/24/17.
//

#ifndef VAPEENGINE_GAMEMANAGER_H
#define VAPEENGINE_GAMEMANAGER_H

#include "InputManager.h"
#include "SceneManager.h"
#include <cstdio>
#include <renderer/RenderManager.h>
#include <renderer/PrimitiveRenderer.h>
#include <test_object/Player.h>
#include <editor/Editor.h>

namespace Core {

    class GameManager {
    public:
        static GameManager &getInstance() {
            static GameManager instance; // Guaranteed to be destroyed.
            return instance;
        }

        GameManager(GameManager const &) = delete;
        void operator=(GameManager const &) = delete;

        void init();
        void gameLoop(bool _editor);
        void shutDown() { m_bShutdown = true; }
        void signalRunGame();

        inline bool isInitialized() const { return m_bInitialized; }
        static inline double getCurTime() { return glfwGetTime(); }
        GLFWwindow* getWindow() const { return m_window; }

    private:
        GameManager() = default;

        GLFWwindow* m_window; // Will most lilkely be removed at some point.

        float m_fCurTime = 0.f;
        float m_fLastTime = 0.f;

        bool m_bInitialized : 1;
        bool m_bShutdown    : 1;

#if EDITOR
        bool m_bRunGame      : 1;
#endif
    };

}
#endif //VAPEENGINE_GAMEMANAGER_H
