//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_CAMERA_H
#define VAPEENGINE_CAMERA_H


#include "VapeGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"

class Camera : public Core::GameObject {
public:
    Camera(Component *_parent, GLFWwindow *_window) : GameObject(_parent), m_window(_window) {};

    Camera(Component *_parent, GLFWwindow *_window, glm::vec3 _pos, float _h_angle, float _v_angle, float _fov)
            : GameObject(_parent), m_fhAngle(_h_angle), m_fvAngle(_v_angle), m_fFov(_fov) {
        m_transform.position = _pos;
    }

    glm::mat4 getMVP(float _deltaTime, glm::mat4 _modelMat);
    inline void sethAngle(const float _h_angle) { m_fhAngle = _h_angle; }
    inline float gethAngle() { return m_fhAngle; }
    inline void setvAngle(const float _v_angle) { m_fvAngle = _v_angle; }
    inline float getvAngle() { return m_fvAngle; }
    inline void setFov(const float _fov) { m_fFov = _fov; }
    inline float getFov() { return m_fFov; }

    void update(const float _deltaTime) override { /* TODO */ }

private:
    glm::mat4 m_modelMat;
    GLFWwindow *m_window;

    float m_fhAngle = 3.14f; // horizontal angle
    float m_fvAngle = 0.0f; // vertical angle
    float m_fFov = 45.0f; // Field of view
};


#endif //VAPEENGINE_CAMERA_H
