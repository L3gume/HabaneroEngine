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
    m_transform.rotation = {
            glm::cos(m_fvAngle) * glm::sin(m_fhAngle),
            glm::sin(m_fvAngle),
            glm::cos(m_fvAngle) * glm::cos(m_fhAngle)
    };

    glm::vec3 right = glm::vec3(
            glm::sin(m_fhAngle - 3.14f / 2.0f),
            0,
            glm::cos(m_fhAngle - 3.14f / 2.0f)
    );

    glm::vec3 up = glm::cross(right, m_transform.rotation);

    glm::mat4 projMat = glm::perspective(glm::radians(m_fFov), 16.0f / 9.0f, 0.1f, 100.0f);

    glm::mat4 viewMat;

    if (m_parent) {
//        glm::vec3 rot = (glm::quat(m_absoluteTransform.rotation) * m_transform.rotation);
//        m_fvAngle = glm::atan(m_transform.rotation.y / m_transform.rotation.x);
//        m_fhAngle = glm::acos(m_transform.rotation.z / static_cast<float>(glm::sqrt(glm::pow(m_transform.rotation.x, 2) + glm::pow(m_transform.rotation.y, 2) + glm::pow(m_transform.rotation.z, 2))));
//        right = glm::vec3(
//                glm::sin(m_fhAngle - 3.14f / 2.0f),
//                0,
//                glm::cos(m_fhAngle - 3.14f / 2.0f)
//        );
//        up = glm::cross(rot, right);
        viewMat = glm::lookAt(
                m_absoluteTransform.position,                       // Camera is here
                m_absoluteTransform.position + (glm::quat(m_absoluteTransform.rotation) * m_transform.rotation), // and looks here : at the same pos, plus "rotation"
                glm::vec3(0.f, 1.f, 0.f)                    // Head is up (set to 0,-1,0 to look upside-down)
        );
    } else {
        viewMat = glm::lookAt(
                m_transform.position,                        // Camera is here
                m_transform.position + m_transform.rotation, // and looks here : at the same pos, plus "rotation"
                glm::vec3(0.f, 1.f, 0.f)                     // Head is up (set to 0,-1,0 to look upside-down)
        );
    }

    return projMat * viewMat * _modelMat;
}

void Camera::update(const float _deltaTime) {
    GameObject::update(_deltaTime);

//    if (m_parent) {
//        m_fvAngle = m_absoluteTransform.rotation.x;
//        m_fhAngle = m_absoluteTransform.rotation.y;
//    }
}