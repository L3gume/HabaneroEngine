#ifndef VAPEENGINE_RENDERSYSTEM_H
#define VAPEENGINE_RENDERSYSTEM_H


#include <ecs/ecs.h>
#include <components/RenderableComponent.h>
#include <core/Engine.h>
#include <common/loadShaders.h>
#include <components/TransformComponent.h>
#include <systems/CameraSystem.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace ECS;

class RenderSystem : public System {
    friend class SystemManager;
public:
    RenderSystem(GLFWwindow* _window/*, Camera* _cam*/);
private:
    void renderEntity(GLuint& v_buf, const Entity* _ent, float _deltaTime);
    void preUpdate(float _deltaTime) override;
    void update(float _deltaTime) override;
    void close();

    std::vector<Entity*> m_renderableEntities;
    GLFWwindow* m_window = nullptr;
//    Camera* m_camera;

    GLuint programID; //Program id

    GLint matID;
    GLint viewID; //View matrix id
    GLint modID; //Model matrix id

    GLint textureID; //Texture sampler id

    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint normalBuffer;
    GLuint elementBuffer;

    GLint lightID; //Light id

    std::vector<GLuint> m_textures = {};
};


#endif //VAPEENGINE_RENDERSYSTEM_H
