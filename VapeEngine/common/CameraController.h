//
// Created by notjustin on 12/19/17.
//

#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

/*
 * TODO: add different modes : freecam (almost done), follow, etc.
 */
class CameraController {
public:
    explicit CameraController(GLFWwindow* _window) : window(_window) { /* Default constructor */ }
    CameraController(GLFWwindow* _window, glm::vec3 _pos, float _h_angle, float _v_angle, float _fov)
            : window(_window), pos(_pos), h_angle(_h_angle), v_angle(_v_angle), fov(_fov) { /* constructor with data stuff */ }

    /* Getters and Setters, implemented in .h file since its basically nothing */
    void setMoveSpeed(float _speed) { speed = _speed; }
    float getMoveSpeed() { return speed; }
    void setMouseSpeed(float _mouse_speed) { mouse_speed = _mouse_speed; }
    float getMouseSpeed() { return mouse_speed; }
    void setFov(float _fov) { fov = _fov; }
    float getFov() { return fov; }

    glm::mat4 render();
private:
    GLFWwindow* window;
    glm::vec3 pos = glm::vec3(0, 0, 5); // Position of the camera
    glm::vec3 rot = glm::vec3(0, 0, 0); // Rotation of the camera
    float h_angle = 3.14f; // horizontal angle
    float v_angle = 0.0f; // vertical angle
    float fov = 45.0f; // Field of view
    float speed = 3.0f; // speed of camera, in units per second
    float mouse_speed = 0.055f; // Mouse sensitivity
    double last_time = 0.0; // used for delta_time computation
    glm::mat4 projMat; // Projection matrix
    glm::mat4 viewMat; // View matrix

    void computeMatricesFromInputs();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
};
#endif //CAMERA_CONTROLLER_H
