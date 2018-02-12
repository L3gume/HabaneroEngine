//
// Created by l3gume on 11/02/18.
//


#include <glm/gtc/matrix_transform.hpp>
#include "CameraSystem.h"

inline void CameraSystem::setActiveCamera(Entity *_cam) noexcept {
    assert(_cam->hasComponent<CameraComponent>() &&
           _cam->hasComponent<TransformComponent>()); // throw an error if its not the case.
    // A camera entity needs both a camera component, which holds the data for the projection matrix,
    // and a transform component, which contains the info about the camera's position and orientation.
    ComponentID typeID = getComponentTypeID<CameraComponent>();
    if (!_cam->hasGroup(typeID)) _cam->addGroup(typeID); // Just in case.
    m_activeCamera = _cam;
}

glm::mat4 CameraSystem::getMVPFromActiveCamera(glm::mat4 _modelMat) {
    return projMat * viewMat * _modelMat;
}

void CameraSystem::preUpdate(float _deltaTime) {
    /*
     * Since we won't be changing cameras during a single frame, generate all the relevant stuff in preUpdate.
     */
    if (m_activeCamera == nullptr) {
        m_cameras = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
                getComponentTypeID<CameraComponent>());
        assert(!m_cameras.empty()); // If there is no registered camera, we won't go very far.
        m_activeCamera = m_cameras[0]; // just pick the first one.
    }

    const TransformComponent &transform = m_activeCamera->getComponent<TransformComponent>();
    const CameraComponent &camera = m_activeCamera->getComponent<CameraComponent>();

    /*
     * The lookAt function likes cartesian coordinates so we do a bunch of conversions.
     */

    cartesianRot = {
            glm::cos(transform.rotation.x) * glm::sin(transform.rotation.y),
            glm::sin(transform.rotation.x),
            glm::cos(transform.rotation.x) * glm::cos(transform.rotation.y)
    };

    cartesianRight = {
            glm::sin(transform.rotation.y - 3.14f / 2.0f),
            0,
            glm::cos(transform.rotation.y - 3.14f / 2.0f)
    };

    cartesianUp = glm::cross(cartesianRight, cartesianRot);

    viewMat = glm::lookAt(
            transform.position,
            transform.position + cartesianRot,
            cartesianUp
    );

    projMat = glm::perspective(glm::radians(camera.m_fov), camera.m_hRes / camera.m_vRes, camera.m_zNear,
                                         camera.m_zFar);
}
