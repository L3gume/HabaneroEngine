//
// Created by notjustin on 1/18/18.
//

#include "Player.h"

void Player::update(float _deltaTime) {
    glm::vec3 pos = m_transform.position;
    // Move forward
    if (m_bMoveForward) {
        pos -= glm::vec3(0.f, 0.f, _deltaTime * m_fSpeed);
    }
    // Move backward
    if (m_bMoveBack) {
        pos += glm::vec3(0.f, 0.f, _deltaTime * m_fSpeed);
    }
    // Strafe right
    if (m_bMoveRight) {
        pos += glm::vec3(_deltaTime * m_fSpeed, 0.f, 0.f);
    }
    // Strafe left
    if (m_bMoveLeft) {
        pos -= glm::vec3(_deltaTime * m_fSpeed , 0.f, 0.f);
    }
    m_transform.position = pos;
}

void Player::onKeyPressed(const KeyboardInputMessage &_kbdMsg) {
    m_bMoveForward = _kbdMsg.KEY_I;
    m_bMoveBack = _kbdMsg.KEY_K;
    m_bMoveLeft = _kbdMsg.KEY_J;
    m_bMoveRight = _kbdMsg.KEY_L;
}
