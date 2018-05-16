//
// Created by notjustin on 12/24/17.
//
#pragma once
#ifndef HABANERO_GAMEMANAGER_H
#define HABANERO_GAMEMANAGER_H

#include <../engine/core/ecs/ecs.h>

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

        void signalRunGame();

        inline bool isInitialized() const { return m_bInitialized; }
        static inline double getCurTime() { return 0; }
//        inline GLFWwindow* getWindow() const { return m_window; }

        inline ECS::EntityManager& getEntityManager() { return m_entityManager; }
        inline ECS::SystemManager& getSystemManager() { return m_systemManager; }
    private:
        Engine() = default;

        ECS::EntityManager m_entityManager;
        ECS::SystemManager m_systemManager;

//        GLFWwindow* m_window; // Will most lilkely be removed at some point.

        float m_fCurTime = 0.f;
        float m_fLastTime = 0.f;

        bool m_bInitialized : 1;
        bool m_bShutdown    : 1;

#if EDITOR
        bool m_bRunGame      : 1;
#endif
    };

}
#endif //HABANERO_GAMEMANAGER_H
