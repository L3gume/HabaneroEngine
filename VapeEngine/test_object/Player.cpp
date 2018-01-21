//
// Created by notjustin on 1/18/18.
//

#include <glm/glm.hpp>
#include "Player.h"

void Player::update(float _deltaTime) {
    GameObject::update(_deltaTime); // won't affect the player

    // Move forward
    if (m_bMoveForward) {
        m_transform.position -= glm::vec3(0.f, 0.f, _deltaTime * m_fSpeed);
    }
    // Move backward
    if (m_bMoveBack) {
        m_transform.position += glm::vec3(0.f, 0.f, _deltaTime * m_fSpeed);
    }
    // Strafe right
    if (m_bMoveRight) {
        m_transform.position += glm::vec3(_deltaTime * m_fSpeed, 0.f, 0.f);
    }
    // Strafe left
    if (m_bMoveLeft) {
        m_transform.position -= glm::vec3(_deltaTime * m_fSpeed, 0.f, 0.f);
    }

    // Rotate Left
    if (m_bTurnLeft) {
        m_transform.rotation += glm::vec3(0.f, _deltaTime * m_fSpeed, 0.f);
    }
    // Rotate Right
    if (m_bTurnRight) {
        m_transform.rotation -= glm::vec3(0.f, _deltaTime * m_fSpeed, 0.f);
    }
}

void Player::onKeyPressed(const KeyboardInputMessage &_kbdMsg) {
    m_bMoveForward = _kbdMsg.KEY_I;
    m_bMoveBack = _kbdMsg.KEY_K;
    m_bMoveLeft = _kbdMsg.KEY_J;
    m_bMoveRight = _kbdMsg.KEY_L;
    m_bTurnLeft = _kbdMsg.KEY_U;
    m_bTurnRight = _kbdMsg.KEY_O;
}
