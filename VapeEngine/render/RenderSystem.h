//
// Created by l3gume on 11/02/18.
//

#ifndef VAPEENGINE_RENDERSYSTEM_H
#define VAPEENGINE_RENDERSYSTEM_H


#include <ecs/ecs.h>
#include <components/RenderableComponent.h>
#include <core/Engine.h>
#include <common/loadShaders.h>
#include <components/TransformComponent.h>


using namespace ECS;

class RenderSystem : public System {
    friend class SystemManager;
public:
    void preUpdate(float _deltaTime) override;
    void update(float _deltaTime) override;
    RenderSystem(GLFWwindow* _window, Camera* _cam);
protected:

private:
    void renderEntity(GLuint& v_buf, const Entity* _ent, float _deltaTime);

    std::vector<Entity*> m_renderableEntities;
    GLFWwindow* m_window = nullptr;
    Camera* m_camera;
    GLint matID;
};


#endif //VAPEENGINE_RENDERSYSTEM_H
