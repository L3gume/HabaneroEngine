//
// Created by notjustin on 12/22/17.
//

#ifndef VAPEENGINE_INPUTMANAGER_H
#define VAPEENGINE_INPUTMANAGER_H

#include <deque>
#include "InputListener.h"
#include "InputMessage.h"

namespace VapeInput {

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

        void init(GLFWwindow* _window);

        bool addInputListener(InputListener* _listener);
        bool removeInputListener(InputListener* _listener);

        void update(GLFWwindow* _window, float _deltaTime);
        void updateScrollInput(double _x, double _y);

#if EDITOR
        void switchMode(bool _gameMode);
#endif
    private:
        InputManager() = default; // Constructor kept private since this is a singleton

        MouseScrolledInputMessage m_scrolledInputMessage = {};

        KeyboardInputMessage getKeyboardInputs(GLFWwindow* _window);
        MouseMovedInputMessage getMouseCoordinates(GLFWwindow* _window);
        MouseClickedInputMessage getMouseInputs(GLFWwindow* _window);

        std::deque<InputListener*> m_listeners; // List of input listeners
    };

} // End of namespace VapeInput

#endif //TUTORIAL_INPUTMANAGER_H
