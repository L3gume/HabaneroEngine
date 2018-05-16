//
// Created by l3gume on 11/02/18.
//
#pragma once
#ifndef HABANERO_CAMERACOMPONENT_H
#define HABANERO_CAMERACOMPONENT_H

#include "engine/core/ecs/ecs.h"

/*
 * IMPORTANT INFO, rotation = {0.f, 0.f, 0.f} means that the camera is pointing towards negative z axis.
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

#endif //HABANERO_CAMERACOMPONENT_H
