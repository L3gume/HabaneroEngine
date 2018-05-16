//
// Created by l3gume on 11/02/18.
//
#pragma once
#ifndef VAPEENGINE_RENDERSYSTEM_H
#define VAPEENGINE_RENDERSYSTEM_H


#include "engine/core/ecs/ecs.h"
#include "engine/core/components/RenderableComponent.h"
#include "engine/core/components/TransformComponent.h"
#include "engine/core/Engine.h"
#include "CameraSystem.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace ECS;

class RenderSystem : public System {
    friend class SystemManager;
	/*
public:
private:
    void renderEntity(GLuint& v_buf, const Entity* _ent, float _deltaTime);
    void preUpdate(float _deltaTime) override;
    void update(float _deltaTime) override;

    std::vector<Entity*> m_renderableEntities;
    GLFWwindow* m_window = nullptr;
//    Camera* m_camera;
    GLint matID;
	*/
};


#endif //VAPEENGINE_RENDERSYSTEM_H
