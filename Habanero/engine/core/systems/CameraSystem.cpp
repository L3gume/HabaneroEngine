//
// Created by l3gume on 11/02/18.
//
#include "CameraSystem.h"

#include "libraries/DirectXTK/include/SimpleMath.h"

using DirectX::Matrix;
using DirectX::Vector3;

inline void CameraSystem::setActiveCamera(Entity *_cam) noexcept {
    assert(_cam->hasComponent<CameraComponent>() &&
           _cam->hasComponent<TransformComponent>()); // throw an error if its not the case.
    // A camera entity needs both a camera component, which holds the data for the projection matrix,
    // and a transform component, which contains the info about the camera's position and orientation.
    ComponentID typeID = getComponentTypeID<CameraComponent>();
    if (!_cam->hasGroup(typeID)) _cam->addGroup(typeID); // Just in case.
    m_activeCamera = _cam;

	UpdateProjectionMatrix();
}

glm::mat4 CameraSystem::getMVPFromActiveCamera(glm::mat4 _modelMat) {
    return projMat * viewMat * _modelMat;
}

void CameraSystem::UpdateProjectionMatrix() {
	const CameraComponent &camera = m_activeCamera->getComponent<CameraComponent>();
	projMat = Matrix::CreatePerspectiveFieldOfViewLH(camera.m_fov, camera.m_hRes / camera.m_vRes,
		camera.m_zNear, camera.m_zFar);
}

void CameraSystem::preUpdate(float _deltaTime) {
    /*
     * Since we won't be changing cameras during a single frame, generate all the relevant stuff in preUpdate.
     */
    if (m_activeCamera == nullptr) {
        const auto& cameras = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
                getComponentTypeID<CameraComponent>());
        assert(!cameras.empty()); // If there is no registered camera, we won't go very far.
        m_activeCamera = cameras[0]; // just pick the first one.
		UpdateProjectionMatrix();
    }

    const TransformComponent &transform = m_activeCamera->getComponent<TransformComponent>();
    const CameraComponent &camera = m_activeCamera->getComponent<CameraComponent>();

	Vector3 cameraTarget = {
            glm::cos(transform.rotation.x) * glm::sin(transform.rotation.y),
            glm::sin(transform.rotation.x),
            glm::cos(transform.rotation.x) * glm::cos(transform.rotation.y)
    };

	viewMat = DirectX::Matrix::CreateLookAtLH(
		transform.position,
		cameraTarget,
		Vector3(0.0f, 1.0f, 0.0f)
	);
}
