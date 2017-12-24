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
        void gameLoop();

        inline bool isInitialized() const { return m_bInitialized; }
    private:
        GameManager() = default;

        GLFWwindow* m_window;

        float m_fCurTime = 0.f;
        float m_fLastTime = 0.f;

        bool m_bInitialized : 1;
    };

}
#endif //VAPEENGINE_GAMEMANAGER_H
