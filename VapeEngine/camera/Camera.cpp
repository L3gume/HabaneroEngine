//
// Created by notjustin on 12/31/17.
//

#include "Camera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
/*
 * _deltaTime is not used, will probably have to be removed
 */
glm::mat4 Camera::getMVP(const float _deltaTime, const glm::mat4 _modelMat) {
    // Reset the camera's rotation in case the angles were updated
    m_transform.euler_rotation = {
            glm::cos(m_fvAngle) * glm::sin(m_fhAngle),
            glm::sin(m_fvAngle),
            glm::cos(m_fvAngle) * glm::cos(m_fhAngle)
    };

    // corresponds to the positive X-axis relative to the camera
    glm::vec3 right = glm::vec3(
            glm::sin(m_fhAngle - 3.14f / 2.0f),
            0,
            glm::cos(m_fhAngle - 3.14f / 2.0f)
    );

    // corresponds to the positive Y-axis relative to the camera
    glm::vec3 up = glm::cross(right, m_transform.euler_rotation);

    // Projection matrix, uses the screen's aspect ratio and the desired FoV
    glm::mat4 projMat = glm::perspective(glm::radians(m_fFov), 16.0f / 9.0f, 0.1f, 100.0f);

    // View matrix, generated using the camera's rotation and position
    glm::mat4 viewMat;
    if (m_parent) {
        /*
         * do things a bit differently if the camera is another object's child
         * TODO: the transform and absoluteTransform probably aren't the best way of doing things.
         */
        const Core::Transform* parentTransform = m_parent->getTransform();
        glm::mat4 rot = glm::toMat4(parentTransform->getQuatRotation());
        up = rot[1]; // y-axis, the new up
        glm::vec3 pos = parentTransform->position + (parentTransform->getQuatRotation() * m_transform.position);
        viewMat = glm::lookAt(
                pos,                       // Camera is here
                pos + (parentTransform->getQuatRotation() * m_transform.euler_rotation), // and looks here : at the same pos, plus "rotation"
                up                    // Head is up (set to 0,-1,0 to look upside-down)
        );
    } else {
        viewMat = glm::lookAt(
                m_transform.position,                        // Camera is here
                m_transform.position + m_transform.euler_rotation, // and looks here : at the same pos, plus "rotation"
                up                     // Head is up (set to 0,-1,0 to look upside-down)
        );
    }

    // return the MVP matrix
    return projMat * viewMat * _modelMat;
}

void Camera::update(const float _deltaTime) {
    GameObject::update(_deltaTime);
}