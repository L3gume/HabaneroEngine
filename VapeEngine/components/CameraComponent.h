//
// Created by l3gume on 11/02/18.
//

#ifndef VAPEENGINE_CAMERACOMPONENT_H
#define VAPEENGINE_CAMERACOMPONENT_H

#include <ecs/ecs.h>
#include <glm/matrix.hpp>

/*
 * IMPORTANT INFO, rotation = {0, 0, 0} means that the camera is pointing towards negative z axis.
 */
struct CameraComponent : ECS::Component {
    CameraComponent(float _fov, float _hRes, float _vRes, float _zNear, float _zFar)
            : m_fov(_fov), m_hRes(_hRes), m_vRes(_vRes), m_zNear(_zNear), m_zFar(_zFar) {}

    float m_fov;
    float m_hRes;
    float m_vRes;
    float m_zNear;
    float m_zFar;
};

#endif //VAPEENGINE_CAMERACOMPONENT_H
