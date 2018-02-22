//
// Created by notjustin on 12/24/17.
//

#ifndef VAPEENGINE_GAMEMANAGER_H
#define VAPEENGINE_GAMEMANAGER_H

#include "InputManager.h"
#include <cstdio>
#include <test_object/Player.h>
#include <editor/Editor.h>
#include <ecs/ecs.h>
#include <editor/EditorCamera.h>

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
        void gameLoop(bool _editor);
        void shutDown() { m_bShutdown = true; }
        void reset();

        void switchMode();
        void signalRunGame();

        inline bool isInitialized() const { return m_bInitialized; }
        static inline double getCurTime() { return glfwGetTime(); }
        inline GLFWwindow* getWindow() const { return m_window; }

        inline ECS::EntityManager& getEntityManager() { return m_entityManager; }
        inline ECS::SystemManager& getSystemManager() { return m_systemManager; }

#if EDITOR
        inline bool gameRunning() { return m_bRunGame; }
        inline EditorCamera& getEditorCam() { return m_freeCam; }
#endif
#if EDITOR
    private:
        Engine() : m_freeCam(EditorCamera(nullptr)) {}
#else
        Engine() = default;
#endif
        ECS::EntityManager m_entityManager;
        ECS::SystemManager m_systemManager;

        GLFWwindow* m_window; // Will most lilkely be removed at some point.

        float m_fCurTime = 0.f;
        float m_fLastTime = 0.f;

        bool m_bInitialized : 1;
        bool m_bShutdown    : 1;
        bool m_bSwitchMode  : 1;

#if EDITOR
        bool m_bRunGame      : 1;

        EditorCamera m_freeCam;
#endif
    };

}
#endif //VAPEENGINE_GAMEMANAGER_H
