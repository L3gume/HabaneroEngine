//
// Created by notjustin on 1/18/18.
//

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <common/quatUtils.h>
#include "Player.h"

void Player::update(float _deltaTime) {
    GameObject::update(_deltaTime); // won't affect the player

    glm::quat qRot = m_transform.getQuatRotation();
    glm::mat4 rot = glm::toMat4(qRot);
    glm::vec3 right = rot[0];
    glm::vec3 up = rot[1];
    glm::vec3 frwd = rot[2];

    // Move forward
    if (m_bMoveForward) {
        m_transform.position -= frwd * _deltaTime * m_fSpeed;
    }
    // Move backward
    if (m_bMoveBack) {
        m_transform.position += frwd * _deltaTime * m_fSpeed;
    }
    // Strafe right
    if (m_bMoveRight) {
        m_transform.position += right * _deltaTime * m_fSpeed;
    }
    // Strafe left
    if (m_bMoveLeft) {
        m_transform.position -= right * _deltaTime * m_fSpeed;
    }
    // Rotate Left
    if (m_bTurnLeft) {
        m_transform.euler_rotation = glm::eulerAngles(glm::angleAxis(_deltaTime * m_fSpeed, up) * m_transform.getQuatRotation());
    }
    // Rotate Right
    if (m_bTurnRight) {
        m_transform.euler_rotation = glm::eulerAngles(glm::angleAxis(-(_deltaTime * m_fSpeed), up) * m_transform.getQuatRotation());
    }
    // barrel roll Left
    if (m_bTurnLeftSide) {
        m_transform.euler_rotation = glm::eulerAngles(glm::angleAxis(_deltaTime * m_fSpeed, frwd) * m_transform.getQuatRotation());
    }
    // barrel roll Right
    if (m_bTurnRightSide) {
        m_transform.euler_rotation = glm::eulerAngles(glm::angleAxis(-(_deltaTime * m_fSpeed), frwd) * m_transform.getQuatRotation());
    }
}

void Player::onKeyPressed(const KeyboardInputMessage &_kbdMsg) {
    m_bMoveForward = _kbdMsg.KEY_I;
    m_bMoveBack = _kbdMsg.KEY_K;
    m_bMoveLeft = _kbdMsg.KEY_J;
    m_bMoveRight = _kbdMsg.KEY_L;
    m_bTurnLeft = _kbdMsg.KEY_U;
    m_bTurnRight = _kbdMsg.KEY_O;
    m_bTurnLeftSide = _kbdMsg.KEY_N;
    m_bTurnRightSide = _kbdMsg.KEY_M;
}
