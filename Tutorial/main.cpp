#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "common/loadShaders.h"

//
// Following tutorial on:
// http://www.opengl-tutorial.org
//
int main() {

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // OpenGL 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = nullptr;
    window = glfwCreateWindow(1280, 720, "Tutorial 01", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFWwindow.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = (GLboolean) true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // TODO: change the path when we are not in DEBUG
    GLuint programID = loadShaders("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    GLint matID = glGetUniformLocation(programID, "MVP");

    do {
        /* Draw a triangle */
        GLuint vertexArrayID;
        glGenVertexArrays(1, &vertexArrayID);
        glBindVertexArray(vertexArrayID);

        static const GLfloat g_vertex_buf_data[] = {
                -1.f, -1.f, 0.f,
                1.f, -1.f, 0.f,
                0.f, 1.f, 0.f
        };

        GLuint vertex_buf; // identify the vertex buffer
        glGenBuffers(1, &vertex_buf); // generate 1 buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buf_data), g_vertex_buf_data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buf);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        /* Do the camera ting */
        // Projection matrix: 45 deg FOV, 16:9 ratio, disp range: 0.1 units to 100 units
        glm::mat4 proj = glm::perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.f);
        // Camera matrix
        glm::mat4 view = glm::lookAt(glm::vec3(-3, 5, 2), // Camera's position
                                     glm::vec3(0, 0, 0), // looks at origin
                                     glm::vec3(0, 1, 0)  // Head is up (0, -1, 0) to look upside-down
        );

        // Model matrix
        glm::mat4 model = glm::mat4(1.f);
        // ModelViewProjection
        glm::mat4 mvp = proj * view * model; // actual mult is done the other way around

        glUniformMatrix4fv(matID, 1, GL_FALSE, &mvp[0][0]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

    return 0;
}