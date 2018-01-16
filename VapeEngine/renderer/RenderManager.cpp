#include <GL/glew.h>
#include <common/loadShaders.h>
#include <core/GameObject.h>
#include "RenderManager.h"
#include "PrimitiveShapes.h"
#include "PrimitiveRenderer.h"

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
//    glEnable(GL_CULL_FACE);

}

void VapeRenderer::RenderManager::update(/*GameScene as parameter*/GLFWwindow* _window, float _deltaTime, CameraController *cc) {
    //For every game object in gamescene, render them

    //Do the camera ting
    GLuint vertex_buf; // identify the vertex buffer
    glGenBuffers(1, &vertex_buf); // generate 1 buffer

    glm::mat4 MVP; //MVP matrix


    //TODO: Replace this with an actual games scene
    auto cube = new Core::GameObject(nullptr, new VapeRenderer::PrimitiveRenderer(VapeRenderer::CUBE));
    Core::Transform* cubeTF = cube->getTransform();
    cubeTF->position = glm::vec3(0.f, 1.f, 0.f);

    auto plane = new Core::GameObject(nullptr, new VapeRenderer::PrimitiveRenderer(VapeRenderer::PLANE));
    Core::Transform* planeTF = plane->getTransform();
    planeTF->scale = glm::vec3(10.f, 1.f, 10.f);

    std::vector<Core::GameObject*> gameObjects;
    gameObjects.emplace_back(cube);
    gameObjects.emplace_back(plane);

    

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    for (auto &gameObject : gameObjects) {
        Core::Transform* transform = gameObject->getTransform();

        glm::mat4 translate = glm::translate(glm::mat4(1.0f), transform->position);
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 90.0f, transform->rotation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0), transform->scale);

        if (transform->rotation == glm::vec3(0.f, 0.f, 0.f)) { //If no rotation, don't multiply by 0
            rotate = glm::mat4();
        }

        MVP = (*cc).getMVP(_deltaTime, translate * rotate * scale);

        glUniformMatrix4fv(matID, 1, GL_FALSE, &MVP[0][0]);
        gameObject->getRenderer()->render(&vertex_buf);
    }

    glDisable(GL_CULL_FACE);
    glDisableVertexAttribArray(0);

    glfwSwapBuffers(_window);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}