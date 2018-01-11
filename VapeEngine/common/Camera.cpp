//
// Created by notjustin on 12/31/17.
//

#include "Camera.h"

glm::mat4 Camera::getMVP(const float _deltaTime, const glm::mat4 _modelMat) {
    // Right vector
//    glm::vec3 right = glm::vec3(
//            glm::sin(m_fhAngle - 3.14f / 2.0f),
//            0,
//            glm::cos(m_fhAngle - 3.14f / 2.0f)
//    );
//    // Up vector : perpendicular to both m_rot and right
//    glm::vec3 up = glm::cross(right, m_transform.rotation);
    glm::mat4 projMat = glm::perspective(glm::radians(m_fFov), 16.0f / 9.0f, 0.1f, 100.0f);
    glm::mat4 viewMat = glm::lookAt(
            m_transform.position,           // Camera is here
            m_transform.position + m_transform.rotation, // and looks here : at the same pos, plus "m_rot"
            /*up*/glm::vec3(0, 1, 0)                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    return projMat * viewMat * _modelMat;
}