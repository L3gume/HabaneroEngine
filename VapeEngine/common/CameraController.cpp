//
// Created by notjustin on 12/19/17.
//
#include <cstdio>
#include "CameraController.h"

glm::mat4 CameraController::render(const float _deltaTime) {
    computeMatricesFromInputs(_deltaTime);
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::mat4(1.0);
    return ProjectionMatrix * ViewMatrix * ModelMatrix;
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
        glfwSetCursorPos(m_window, 1280 / 2, 720 / 2);
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

void CameraController::computeMatricesFromInputs(const float _deltaTime) {
    if (!m_window) {
#ifdef DEBUG
        // TODO create a logging system that opens a console or something
        fprintf(stderr, "window is NULL.\n");
#endif
        return;
    }

    // Compute new orientation
    if (m_dMouseXPos != -1 && m_dMouseYPos != -1 && m_bCaptureMoveMovement && m_bRightClickHeld) {
        m_fhAngle += m_fMouseSpeed * _deltaTime * float(1280 / 2 - m_dMouseXPos);
        m_fvAngle += m_fMouseSpeed * _deltaTime * float(720 / 2 - m_dMouseYPos);
    }

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            glm::cos(m_fvAngle) * glm::sin(m_fhAngle),
            glm::sin(m_fvAngle),
            glm::cos(m_fvAngle) * glm::cos(m_fhAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            glm::sin(m_fhAngle - 3.14f / 2.0f),
            0,
            glm::cos(m_fhAngle - 3.14f / 2.0f)
    );

    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross(right, direction);

    // only allow arrow key movement when right click is held
    if (m_bRightClickHeld) {
        // Move forward
        if (m_bMoveForward) {
            m_pos += direction * _deltaTime * m_fSpeed;
        }
        // Move backward
        if (m_bMoveBack) {
            m_pos -= direction * _deltaTime * m_fSpeed;
        }
        // Strafe right
        if (m_bMoveRight) {
            m_pos += right * _deltaTime * m_fSpeed;
        }
        // Strafe left
        if (m_bMoveLeft) {
            m_pos -= right * _deltaTime * m_fSpeed;
        }
        // go up
        if (m_bMoveUp) {
            m_pos += up * _deltaTime * m_fSpeed;
        }
        // go down
        if (m_bMoveDown) {
            m_pos -= up * _deltaTime * m_fSpeed;
        }
    } else if (m_bMiddleClickHeld) {
        // "drag" screen when holding middle click
        m_pos -= up * 1.5f * m_fMouseSpeed * _deltaTime * ((720 / 2) - (float)m_dMouseYPos);
        m_pos += right * 1.5f * m_fMouseSpeed * _deltaTime * ((1280 / 2) - (float)m_dMouseXPos);
    }

    if (m_bPerspective && !m_bOrthogonal) {
        m_projMat = glm::perspective(glm::radians(m_fFov), 16.0f / 9.0f, 0.1f, 100.0f);
    } else if (!m_bPerspective && m_bOrthogonal) {
#ifdef DEBUG
        fprintf(stderr, "Orthographic view not implemented yet.\n");
#endif
        m_projMat = glm::perspective(glm::radians(m_fFov), 16.0f / 9.0f, 0.1f, 100.0f);
//        m_projMat = glm::ortho(0.f, 1280.f, 0.f, 720.f, 0.1f, 100.f);
    }

    m_viewMat = glm::lookAt(
            m_pos,           // Camera is here
            m_pos + direction, // and looks here : at the same pos, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 CameraController::getProjectionMatrix() {
    return m_projMat;
}

glm::mat4 CameraController::getViewMatrix() {
    return m_viewMat;
}