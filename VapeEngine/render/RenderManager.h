#ifndef VAPEENGINE_RENDERMANAGER_H
#define VAPEENGINE_RENDERMANAGER_H

#include <common/VapeGL.h>
#include <core/Scene.h>
#include <camera/CameraController.h>

namespace VapeRenderer {
    class RenderManager {
    public:
        static RenderManager &getInstance() {
            static RenderManager instance; // Guaranteed to be destroyed.
            return instance;
        }

        RenderManager(RenderManager const &) = delete;

        void init();

        void update(Core::Scene* _scene, GLFWwindow* _window, float _deltaTime, Camera* cc);
    private:
        RenderManager() = default;

        GLint matID;
    };
}

#endif //VAPEENGINE_RENDERMANAGER_H
