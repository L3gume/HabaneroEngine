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

    glm::mat4 MVP = (*cc).getMVP(_deltaTime, glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.f, 0.f)));

    glUniformMatrix4fv(matID, 1, GL_FALSE, &MVP[0][0]);
    glEnable(GL_CULL_FACE);

    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    auto cubeGO = new Core::GameObject(nullptr);

    auto cube = new VapeRenderer::PrimitiveRenderer(cubeGO, VapeRenderer::CUBE);
    cube->render(&vertex_buf);

    MVP = (*cc).getMVP(_deltaTime, glm::scale(glm::mat4(1.f), glm::vec3(10.f, 1.f, 10.f)) * glm::mat4(1.f));

    glUniformMatrix4fv(matID, 1, GL_FALSE, &MVP[0][0]);
    glDisable(GL_CULL_FACE);

    auto planeGO = new Core::GameObject(nullptr);

    auto plane = new VapeRenderer::PrimitiveRenderer(planeGO, VapeRenderer::PLANE);
    plane->render(&vertex_buf);

    glUniformMatrix4fv(matID, 1, GL_FALSE, &MVP[0][0]);

    glfwSwapBuffers(_window);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    // -------------------------------------------------------------------------------------------------------------
    // GHETTO RENDERING: REMOVE THIS WHEN RENDERING SYSTEM IS DONE
    // -------------------------------------------------------------------------------------------------------------
    //Do the camera ting
    /*glm::mat4 MVP = (*cc).getMVP(_deltaTime, glm::translate(glm::mat4(1.f), glm::vec3(0.f, 1.f, 0.f)));

    glUniformMatrix4fv(this->matID, 1, GL_FALSE, &MVP[0][0]);
    glEnable(GL_CULL_FACE);
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color_buffer_data), cube_color_buffer_data, GL_STATIC_DRAW);
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            nullptr                          // array buffer offset
    );

    GLuint vertex_buf; // identify the vertex buffer
    glGenBuffers(1, &vertex_buf); // generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
//        glDisableVertexAttribArray(0);

    //Do the camera ting
    MVP = (*cc).getMVP(_deltaTime, glm::scale(glm::mat4(1.f), glm::vec3(10.f, 1.f, 10.f)) * glm::mat4(1.f));

    glUniformMatrix4fv(this->matID, 1, GL_FALSE, &MVP[0][0]);
    glDisable(GL_CULL_FACE);
    GLuint vertex_buf2; // identify the vertex buffer
    glGenBuffers(1, &vertex_buf2); // generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertex_buffer_data), plane_vertex_buffer_data, GL_STATIC_DRAW);

//        glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDrawArrays(GL_TRIANGLES, 0, 6*3);
    glDisableVertexAttribArray(0);

    glUniformMatrix4fv(matID, 1, GL_FALSE, &MVP[0][0]);

    glfwSwapBuffers(_window);
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
}