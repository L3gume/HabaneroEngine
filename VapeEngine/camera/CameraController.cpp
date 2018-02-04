//
// Created by notjustin on 12/19/17.
//
#include <cstdio>
#include <logging/LogManager.h>
#include "CameraController.h"

glm::mat4 CameraController::getMVP(const float _deltaTime, const glm::mat4 _modelMatrix) {
    computeMatricesFromInputs(_deltaTime);
    return m_camera->getMVP(_deltaTime, _modelMatrix);
}

/*
 * Overridden from InputListener
 * This is going to be called every frame
 */
void CameraController::onKeyPressed(const VapeInput::KeyboardInputMessage& _kbdMsg) {
    m_bMoveForward = _kbdMsg.KEY_W;
    m_bMoveBack = _kbdMsg.KEY_S;
    m_bMoveLeft = _kbdMsg.KEY_A;
    m_bMoveRight = _kbdMsg.KEY_D;
    m_bMoveUp = _kbdMsg.KEY_SPACE;
    m_bMoveDown = _kbdMsg.KEY_LEFT_SHIFT;

    if (_kbdMsg.KEY_P && !m_bPerspective) {
        m_bPerspective = true;
        m_bOrthogonal = false;
    } else if (_kbdMsg.KEY_O && !m_bOrthogonal) {
        m_bOrthogonal = true;
        m_bPerspective = false;
    }
}

/*
 * Overridden from InputListener
 * This is going to be called every frame
 */
void CameraController::onMouseMoved(const VapeInput::MouseMovedInputMessage& _msMsg) {
    if (m_bCaptureMoveMovement) {
        // We only want to use the mouse movement when right click is held down
        m_dMouseXPos = _msMsg.m_dXPos;
        m_dMouseYPos = _msMsg.m_dYPos;
        glfwSetCursorPos(m_window, x_res / 2, y_res / 2);
    }
}

/*
 * Overridden from InputListener
 * This is going to be called every frame
 */
void CameraController::onMousePressed(const VapeInput::MouseClickedInputMessage& _msMsg) {
    if (_msMsg.MOUSE_BUTTON_RIGHT) {
        // We only want to use the mouse movement when right click is held down
        if (!m_bRightClickHeld) {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_bRightClickHeld = true;
            m_bCaptureMoveMovement = true; // flip the bit
        }
    } else if (_msMsg.MOUSE_BUTTON_MIDDLE) {
        if (!m_bMiddleClickHeld) {
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_bMiddleClickHeld = true;
            m_bCaptureMoveMovement = true;
        }
    } else {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        m_bRightClickHeld = false;
        m_bMiddleClickHeld = false;
        m_bCaptureMoveMovement = false;
    }
}

void CameraController::onMouseScrolled(const VapeInput::MouseScrolledInputMessage& _msMsg) {
    if (m_bRightClickHeld) {
        m_fSpeed += _msMsg.m_dXOffset / 7.f;
        if (m_fSpeed < 0.f) {
            m_fSpeed = 1.f;
        } else if (m_fSpeed > m_fMaxSpeed) {
            m_fSpeed = m_fMaxSpeed;
        }
    } else {
        m_camera->getTransform()->position += m_camera->getTransform()->euler_rotation * (static_cast<float>(_msMsg.m_dXOffset) / 5.f);
    }
}

void CameraController::computeMatricesFromInputs(const float _deltaTime) {
    if (!m_window) {
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::COMMON, VapeLog::LogType::ISSUE,
                VapeLog::LogSeverity::CRITICAL, "Passed window is NULL"));
#endif
        return;
    }

    float hAngle = m_camera->gethAngle();
    float vAngle = m_camera->getvAngle();

    // Compute new orientation
    if (m_dMouseXPos != -1 && m_dMouseYPos != -1 && m_bCaptureMoveMovement && m_bRightClickHeld) {
        hAngle += m_fMouseSpeed * _deltaTime * float(x_res / 2 - m_dMouseXPos);
        vAngle += m_fMouseSpeed * _deltaTime * float(y_res / 2 - m_dMouseYPos);
    }
    m_camera->getTransform()->euler_rotation = {
            glm::cos(vAngle) * glm::sin(hAngle),
            glm::sin(vAngle),
            glm::cos(vAngle) * glm::cos(hAngle)
    };

    // Right vector
    glm::vec3 right = glm::vec3(
            glm::sin(hAngle - 3.14f / 2.0f),
            0,
            glm::cos(hAngle - 3.14f / 2.0f)
    );

    glm::vec3 camRot = m_camera->getTransform()->euler_rotation;
    glm::vec3 camPos = m_camera->getTransform()->position;

    // Up vector : perpendicular to both m_rot and right
    glm::vec3 up = glm::cross(right, camRot);

    // only allow arrow key movement when right click is held
    if (m_bRightClickHeld) {
        // Move forward
        if (m_bMoveForward) {
            camPos += camRot * _deltaTime * m_fSpeed;
        }
        // Move backward
        if (m_bMoveBack) {
            camPos -= camRot * _deltaTime * m_fSpeed;
        }
        // Strafe right
        if (m_bMoveRight) {
            camPos += right * _deltaTime * m_fSpeed;
        }
        // Strafe left
        if (m_bMoveLeft) {
            camPos -= right * _deltaTime * m_fSpeed;
        }
        // go up
        if (m_bMoveUp) {
            camPos += up * _deltaTime * m_fSpeed;
        }
        // go down
        if (m_bMoveDown) {
            camPos -= up * _deltaTime * m_fSpeed;
        }
    } else if (m_bMiddleClickHeld) {
        // "drag" screen when holding middle click
        camPos -= up * 1.5f * m_fMouseSpeed * _deltaTime * ((y_res / 2) - (float)m_dMouseYPos);
        camPos += right * 1.5f * m_fMouseSpeed * _deltaTime * ((x_res / 2) - (float)m_dMouseXPos);
    }

    m_camera->getTransform()->euler_rotation = camRot;
    m_camera->getTransform()->position = camPos;
    m_camera->sethAngle(hAngle);
    m_camera->setvAngle(vAngle);
}