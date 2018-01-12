//
// Created by notjustin on 12/31/17.
//

#include "Camera.h"

/*
 * _deltaTime is not used, will probably have to be removed
 */
glm::mat4 Camera::getMVP(const float _deltaTime, const glm::mat4 _modelMat) {
    glm::mat4 projMat = glm::perspective(glm::radians(m_fFov), 16.0f / 9.0f, 0.1f, 100.0f);
    glm::mat4 viewMat = glm::lookAt(
            m_transform.position,                        // Camera is here
            m_transform.position + m_transform.rotation, // and looks here : at the same pos, plus "m_rot"
            glm::vec3(0, 1, 0)                     // Head is up (set to 0,-1,0 to look upside-down)
    );

    return projMat * viewMat * _modelMat;
}