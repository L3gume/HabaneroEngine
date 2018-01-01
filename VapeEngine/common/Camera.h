//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_CAMERA_H
#define VAPEENGINE_CAMERA_H


#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
    Camera();

private:
    glm::mat4 m_transform;
    glm::mat4 m_modelMat;

    GLFWwindow* m_window;
    glm::vec3 m_pos = glm::vec3(0.f, 0.f, 5.f); // Position of the camera
    glm::vec3 m_rot = glm::vec3(0.f, 0.f, 0.f); // Rotation of the camera
    float m_fhAngle = 3.14f; // horizontal angle
    float m_fvAngle = 0.0f; // vertical angle
    float m_fFov = 45.0f; // Field of view
};


#endif //VAPEENGINE_CAMERA_H
