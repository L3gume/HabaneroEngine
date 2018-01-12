//
// Created by notjustin on 12/19/17.
//

#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "InputListener.h"
#include "InputMessage.h"
#include "VapeGL.h"
#include "Camera.h"

/*
 * TODO: Make it possible to move back and forward with scrollwheel while right click is not held
 */
class CameraController : public VapeInput::InputListener {
public:
    explicit CameraController(GLFWwindow* _window) : InputListener(true, true, true, true, true), m_window(_window),
                                                     m_bMoveForward(false), m_bMoveBack(false), m_bMoveLeft(false),
                                                     m_bMoveRight(false), m_bMoveUp(false),
                                                     m_bMoveDown(false), m_bCaptureMoveMovement(false),
                                                     m_bRightClickHeld(false), m_bMiddleClickHeld(false),
                                                     m_bPerspective(true), m_bOrthogonal(false),
                                                     m_camera(nullptr) { /* Default constructor */ }

//    CameraController(GLFWwindow *_window, Camera* _camera, glm::vec3 _pos, float _h_angle, float _v_angle, float _fov)
//            : InputListener(true, true, true, false, true), m_window(_window), m_pos(_pos), m_fhAngle(_h_angle),
//              m_fvAngle(_v_angle), m_fFov(_fov), m_bMoveForward(false), m_bMoveBack(false), m_bMoveLeft(false),
//              m_bMoveRight(false), m_bMoveUp(false), m_bMoveDown(false), m_bCaptureMoveMovement(false),
//              m_bRightClickHeld(false), m_bMiddleClickHeld(false), m_bPerspective(true),
//              m_bOrthogonal(false) { /* constructor with data stuff */ }

    CameraController(GLFWwindow* _window, Camera* _camera)
            : InputListener(true, true, true, false, true), m_window(_window), m_camera(_camera), m_bMoveForward(false), m_bMoveBack(false), m_bMoveLeft(false),
              m_bMoveRight(false), m_bMoveUp(false), m_bMoveDown(false), m_bCaptureMoveMovement(false),
              m_bRightClickHeld(false), m_bMiddleClickHeld(false), m_bPerspective(true),
              m_bOrthogonal(false) { /* constructor with data stuff */ }
    /* Getters and Setters, implemented in .h file since its basically nothing */
    inline void setMoveSpeed(float _speed) { m_fSpeed = _speed; }
    inline float getMoveSpeed() const { return m_fSpeed; }
    inline void setMouseSpeed(float _mouse_speed) { m_fMouseSpeed = _mouse_speed; }
    inline float getMouseSpeed() const { return m_fMouseSpeed; }
    inline void setFov(float _fov) { m_fFov = _fov; }
    inline float getFov() const { return m_fFov; }
    inline void setCamera(Camera* _camera) { m_camera = _camera; }
    inline Camera* getCamera() { return m_camera; }

    void onKeyPressed(const VapeInput::KeyboardInputMessage &_kbdMsg) override;
    void onMouseMoved(const VapeInput::MouseMovedInputMessage &_msMsg) override;
    void onMousePressed(const VapeInput::MouseClickedInputMessage &_msMsg) override;
    void onMouseScrolled(const VapeInput::MouseScrolledInputMessage &_msMsg) override;
    glm::mat4 getMVP(float _deltaTime, glm::mat4 _modelMatrix);

private:
    void computeMatricesFromInputs(float _deltaTime);
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

    GLFWwindow *m_window;
    Camera *m_camera;

    glm::vec3 m_pos = glm::vec3(0.f, 0.f, 5.f); // Position of the camera
    glm::vec3 m_rot = glm::vec3(0.f, 0.f, 0.f); // Rotation of the camera
    float m_fhAngle = 3.14f; // horizontal angle
    float m_fvAngle = 0.0f; // vertical angle
    float m_fFov = 45.0f; // Field of view
    float m_fSpeed = 3.0f; // speed of camera, in units per second
    float m_fMaxSpeed = 40.f;
    float m_fMouseSpeed = 0.055f; // Mouse sensitivity
    glm::mat4 m_projMat; // Projection matrix
    glm::mat4 m_viewMat; // View matrix
    glm::mat4 m_rotMat;

    /* Mouse position */
    double m_dMouseXPos = -1.0;
    double m_dMouseYPos = -1.0;

    /* Movement bits */
    bool m_bMoveForward         : 1;
    bool m_bMoveBack            : 1;
    bool m_bMoveLeft            : 1;
    bool m_bMoveRight           : 1;
    bool m_bMoveUp              : 1;
    bool m_bMoveDown            : 1;
    /* Flags */
    bool m_bCaptureMoveMovement : 1; // Indicates whether or not to move the camera with the mouse
    bool m_bRightClickHeld      : 1; // Indicates that the right mouse button is held
    bool m_bMiddleClickHeld     : 1; // Indicates that the scroll wheel button is held
    bool m_bPerspective         : 1; // Perspective view mode
    bool m_bOrthogonal          : 1; // Orthogonal view mode
};

#endif //CAMERA_CONTROLLER_H
