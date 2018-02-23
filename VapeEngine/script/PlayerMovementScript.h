//
// Created by l3gume on 12/02/18.
//

#ifndef VAPEENGINE_PLAYERSCRIPT_H
#define VAPEENGINE_PLAYERSCRIPT_H

#include <input/InputListener.h>
#include <input/InputMessage.h>
#include <components/TransformComponent.h>
#include <components/ScriptComponent.h>
#include <input/InputManager.h>

using namespace VapeInput;

class PlayerMovementScript : public Script, public InputListener {
public:
    PlayerMovementScript() : InputListener(true, false, false, false, false) {
        m_sName = "PlayerMovementScript";
        m_bMoveForward = false;
        m_bMoveBack = false;
        m_bMoveLeft = false;
        m_bMoveRight = false;
        m_bTurnLeft = false;
        m_bTurnRight = false;
        InputManager::getInstance().addInputListener(this);
    }
    ~PlayerMovementScript() override {
        InputManager::getInstance().removeInputListener(this);
    }

    float m_fSpeed = 10.f;
    TransformComponent *transform = nullptr;

    void init() override;
    void preUpdate(float _deltaTime) override {}
    void update(float _deltaTime) override;
    void postUpdate(float _deltaTime) override {}
    void onKeyPressed(const KeyboardInputMessage &_kbdMsg) override;
    void onMouseMoved(const MouseMovedInputMessage &_msMsg) {}
    void onMousePressed(const MouseClickedInputMessage &_msMsg) {}
    void onMouseScrolled(const MouseScrolledInputMessage &_msMsg) {}

private:
    bool m_bMoveForward     : 1;
    bool m_bMoveBack        : 1;
    bool m_bMoveLeft        : 1;
    bool m_bMoveRight       : 1;
    bool m_bTurnLeft        : 1;
    bool m_bTurnRight       : 1;
};


#endif //VAPEENGINE_PLAYERSCRIPT_H
