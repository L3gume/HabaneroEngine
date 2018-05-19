//
// Created by notjustin on 12/22/17.
//
#pragma once
#ifndef HABANERO_INPUTMANAGER_H
#define HABANERO_INPUTMANAGER_H

#include <windows.h>
#include <deque>
#include "InputListener.h"
#include "InputMessage.h"
#include "../libraries/DirectXTK/include/Keyboard.h"
#include "../libraries/DirectXTK/include/Mouse.h"

namespace Input {

    //
    // Input Manager, implemented as a singleton since we only really want one For now, it will only take inputs for one player.
    //
    class InputManager {
    public:
        static InputManager &getInstance() {
            static InputManager instance; // Guaranteed to be destroyed.
            return instance;
        }

        InputManager(InputManager const &) = delete;
        void operator=(InputManager const &) = delete;

        void init(HWND _window);

        bool addInputListener(InputListener* _listener);
        bool removeInputListener(InputListener* _listener);

        void update();
        void updateScrollInput(double _x, double _y);
    private:
		InputManager() = default; // Constructor kept private since this is a singleton
		
		std::unique_ptr<DirectX::Keyboard> m_pKeyboard;
		std::unique_ptr<DirectX::Mouse> m_pMouse;
		std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_pKeyboardTracker;
		std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_pMouseTracker;

        MouseScrolledInputMessage m_scrolledInputMessage = {};

        KeyboardInputMessage getKeyboardInputs(DirectX::Keyboard::KeyboardStateTracker* _tracker);
        MouseMovedInputMessage getMouseCoordinates(DirectX::Mouse* _mouse);
        MouseClickedInputMessage getMouseInputs(DirectX::Mouse::ButtonStateTracker* _tracker);

        std::deque<InputListener*> m_listeners; // List of input listeners
    };

} // End of namespace VapeInput

#endif //TUTORIAL_INPUTMANAGER_H
