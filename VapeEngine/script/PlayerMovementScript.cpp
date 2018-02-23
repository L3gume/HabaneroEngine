//
// Created by l3gume on 12/02/18.
//

#include <glm/detail/type_mat.hpp>
#include <glm/gtx/quaternion.hpp>
#include "PlayerMovementScript.h"

void PlayerMovementScript::init() {
    Script::init();
    assert(m_entity->hasComponent<TransformComponent>());
    transform = &m_entity->getComponent<TransformComponent>();
}

void PlayerMovementScript::onKeyPressed(const KeyboardInputMessage &_kbdMsg) {
    m_bMoveForward = _kbdMsg.KEY_I;
    m_bMoveBack = _kbdMsg.KEY_K;
    m_bMoveLeft = _kbdMsg.KEY_J;
    m_bMoveRight = _kbdMsg.KEY_L;
    m_bTurnLeft = _kbdMsg.KEY_U;
    m_bTurnRight = _kbdMsg.KEY_O;
}

void PlayerMovementScript::update(float _deltaTime) {
    glm::mat4 rot = glm::toMat4(glm::quat(transform->rotation));
    glm::vec3 right = rot[0];
    glm::vec3 up = rot[1];
    glm::vec3 frwd = rot[2];

    // Move forward
    if (m_bMoveForward) {
        transform->position += frwd * _deltaTime * m_fSpeed;
    }
    // Move backward
    if (m_bMoveBack) {
        transform->position -= frwd * _deltaTime * m_fSpeed;
    }
    // Strafe right
    if (m_bMoveRight) {
        transform->position -= right * _deltaTime * m_fSpeed;
    }
    // Strafe left
    if (m_bMoveLeft) {
        transform->position += right * _deltaTime * m_fSpeed;
    }
    // Rotate Left
    if (m_bTurnLeft) {
        transform->rotation = glm::eulerAngles(glm::angleAxis(_deltaTime * m_fSpeed / 2.f, up) * glm::quat(transform->rotation));
//        transform->rotation += glm::vec3(0.f, m_fSpeed * _deltaTime, 0.f);
    }
    // Rotate Right
    if (m_bTurnRight) {
        transform->rotation = glm::eulerAngles(glm::angleAxis(-(_deltaTime * m_fSpeed / 2.f), up) * glm::quat(transform->rotation));
//        transform->rotation -= glm::vec3(0.f, m_fSpeed * _deltaTime, 0.f);
    }
//    if (transform->rotation.y > glm::radians(360.f)) {
//        transform->rotation.y -= glm::radians(360.f);
//    } else if (transform->rotation.y < glm::radians(0.f)) {
//        transform->rotation.y += glm::radians(360.f);
//    }
}
