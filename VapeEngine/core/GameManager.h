//
// Created by notjustin on 12/24/17.
//

#ifndef VAPEENGINE_GAMEMANAGER_H
#define VAPEENGINE_GAMEMANAGER_H

#include "InputManager.h"

namespace Vape {

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

        inline bool isInitialized() const { return m_bInitialized; }
        static inline double getCurTime() { return glfwGetTime(); }
        GLFWwindow* getWindow() const { return m_window; }

    private:
        GameManager() = default;

        GLFWwindow* m_window; // Will most lilkely be removed at some point.

        float m_fCurTime = 0.f;
        float m_fLastTime = 0.f;

        bool m_bInitialized : 1;
    };

}
#endif //VAPEENGINE_GAMEMANAGER_H
