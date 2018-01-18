//
// Created by notjustin on 1/18/18.
//

#ifndef VAPEENGINE_PLAYER_H
#define VAPEENGINE_PLAYER_H


#include <input/InputListener.h>
#include <core/GameObject.h>
#include <input/InputMessage.h>

using namespace VapeInput;

class Player : public Core::GameObject, public VapeInput::InputListener {
public:
    Player() : GameObject(nullptr), InputListener(true, false, false, false, false),
               m_bMoveForward(false), m_bMoveBack(false), m_bMoveRight(false), m_bMoveLeft(false) {}

    float m_fSpeed = 5.f;

    void update(float _deltaTime) override;

    void onKeyPressed(const KeyboardInputMessage &_kbdMsg) override;
    void onMouseMoved(const MouseMovedInputMessage &_msMsg) {}
    void onMousePressed(const MouseClickedInputMessage &_msMsg) {}
    void onMouseScrolled(const MouseScrolledInputMessage &_msMsg) {}

private:
    bool m_bMoveForward     : 1;
    bool m_bMoveBack        : 1;
    bool m_bMoveLeft        : 1;
    bool m_bMoveRight       : 1;
};


#endif //VAPEENGINE_PLAYER_H
