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
    explicit CameraController(GLFWwindow* _window) : m_window(_window) { /* Default constructor */ }
    CameraController(GLFWwindow* _window, glm::vec3 _pos, float _h_angle, float _v_angle, float _fov)
            : m_window(_window), m_pos(_pos), m_fhAngle(_h_angle), m_fvAngle(_v_angle), m_fFov(_fov) { /* constructor with data stuff */ }

    /* Getters and Setters, implemented in .h file since its basically nothing */
    void setMoveSpeed(float _speed) { m_fSpeed = _speed; }
    float getMoveSpeed() { return m_fSpeed; }
    void setMouseSpeed(float _mouse_speed) { m_fMouseSpeed = _mouse_speed; }
    float getMouseSpeed() { return m_fMouseSpeed; }
    void setFov(float _fov) { m_fFov = _fov; }
    float getFov() { return m_fFov; }

    glm::mat4 render();
private:
    GLFWwindow* m_window;
    glm::vec3 m_pos = glm::vec3(0, 0, 5); // Position of the camera
    glm::vec3 m_rot = glm::vec3(0, 0, 0); // Rotation of the camera
    float m_fhAngle = 3.14f; // horizontal angle
    float m_fvAngle = 0.0f; // vertical angle
    float m_fFov = 45.0f; // Field of view
    float m_fSpeed = 3.0f; // speed of camera, in units per second
    float m_fMouseSpeed = 0.055f; // Mouse sensitivity
    double m_dLastTime = 0.0; // used for delta_time computation
    glm::mat4 m_projMat; // Projection matrix
    glm::mat4 m_viewMat; // View matrix
    glm::mat4 m_rotMat;

    void computeMatricesFromInputs();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
};
#endif //CAMERA_CONTROLLER_H
