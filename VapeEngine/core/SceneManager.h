//
// Created by notjustin on 1/16/18.
//

#ifndef VAPEENGINE_SCENEMANAGER_H
#define VAPEENGINE_SCENEMANAGER_H

#include "Scene.h"

namespace Core {

    // Singleton
    class SceneManager {
    public:
        static SceneManager &getInstance() {
            static SceneManager instance; // Guaranteed to be destroyed.
            return instance;
        }

        SceneManager(SceneManager const &) = delete;
        void operator=(SceneManager const &) = delete;

        void setActiveScene(Scene* _scene) { m_activeScene = _scene; }
        Scene* getActiveScene() { return m_activeScene; }

        void backupActiveScene(); // push current scene to stack (for entering play mode)
        void restorePreviousScene(); // when leaving play mode

    private:
        SceneManager() = default;

        Scene* m_activeScene = nullptr;
    };

}
#endif //VAPEENGINE_SCENEMANAGER_H
