#ifndef VAPEENGINE_RENDERMANAGER_H
#define VAPEENGINE_RENDERMANAGER_H

#include <GLFW/glfw3.h>
#include <core/Scene.h>
#include <common/CameraController.h>

namespace VapeRenderer {
    class RenderManager {
    public:
        static RenderManager &getInstance() {
            static RenderManager instance; // Guaranteed to be destroyed.
            return instance;
        }

        RenderManager(RenderManager const &) = delete;

        void init();

        void update(Core::Scene* _scene, GLFWwindow* _window, float _deltaTime, CameraController *cc);
    private:
        RenderManager() = default;

        GLint matID;
    };
}

#endif //VAPEENGINE_RENDERMANAGER_H
