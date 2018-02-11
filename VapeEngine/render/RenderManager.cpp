
#include <common/loadShaders.h>
#include <core/GameObject.h>
#include <core/Scene.h>
#include <imgui/imgui.h>
#include "RenderManager.h"
#include "quatUtils.h"
#include "ObjectRenderer.h"

void VapeRenderer::RenderManager::init() {
    // TODO: change the path when we are not in DEBUG
    GLuint programID = loadShaders("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    this->matID = glGetUniformLocation(programID, "MVP");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

}

void VapeRenderer::RenderManager::update(Core::Scene* _scene, GLFWwindow* _window, float _deltaTime, Camera* cc) {
    //For every game object in gamescene, render them

    //Do the camera ting
    GLuint vertex_buf; // identify the vertex buffer
    glGenBuffers(1, &vertex_buf); // generate 1 buffer

    glm::mat4 MVP; //MVP matrix

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    for (Core::GameObject* gameObject : *(_scene->getObjects())) {

        const Core::Transform* transform = gameObject->getTransform();

        glm::mat4 translate;
        glm::mat4 rotate;
        glm::mat4 scale;

        if (gameObject->getParent() != nullptr) {
            const Core::Transform* parentTransform = gameObject->getParent()->getTransform();
            translate = glm::translate(glm::mat4(1.f), parentTransform->position +
                                                       parentTransform->getQuatRotation() * transform->position);
            rotate = toMat4(parentTransform->getQuatRotation());
            scale = glm::scale(glm::mat4(1.f), transform->scale * parentTransform->scale);
        } else {
            translate = glm::translate(glm::mat4(1.f), transform->position);
            rotate = toMat4(transform->getQuatRotation());
            scale = glm::scale(glm::mat4(1.f), transform->scale);
        }
        if (transform->euler_rotation == glm::vec3(0.f, 0.f, 0.f) && !gameObject->getParent()) { //If no rotation, don't multiply by 0
            rotate = glm::mat4();
        }

        MVP = cc->getMVP(_deltaTime, translate * rotate * scale);

        glUniformMatrix4fv(matID, 1, GL_FALSE, &MVP[0][0]);

        auto renderer = gameObject->findComponent<ObjectRenderer>();

        if (renderer != nullptr) {
            renderer->render(&vertex_buf);
        }
    }

//    glfwSwapBuffers(_window);
//    glDisable(GL_CULL_FACE);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}