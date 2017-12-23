//
// Created by notjustin on 12/22/17.
//

#ifndef TUTORIAL_INPUTLISTENER_H
#define TUTORIAL_INPUTLISTENER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "InputMessage.h"

namespace VapeInput {
    //
    // Interface for listeners (Abstract class)
    //
    class InputListener {
    public:
        InputListener(bool _useKeyboard, bool _useMouseMov, bool _useMouseButtons, bool _useController) :
                m_bUseKeyboard(_useKeyboard),
                m_bUseMouseMovement(_useMouseMov),
                m_bUseMouseButtons(_useMouseButtons),
                m_bUseController(_useController) {
            // Constructor
        }

        /* For now, responsibility is left to the programmer to delete the listener from the InputManager */
        virtual ~InputListener() = default;

        // Inlining a getter for a simple flag basically saves a function call
        inline bool getUseKeyboard() { return m_bUseKeyboard; }
        inline bool getUseMouseMove() { return m_bUseMouseMovement; }
        inline bool getUseMouseButtons() { return m_bUseMouseButtons; }
        inline bool getUseController() { return m_bUseController; }

        /* These methods have to be overridden by the derived listeners */
        // TODO: Setup a way to pass around inputs, probably an InputEvent struct or just an array of GLFW keycodes
        virtual void onKeyPressed(const KeyboardInputMessage& _kbdMsg, float _deltaTime) = 0;
        virtual void onMouseMoved(const MouseMovedInputMessage& _msMsg, float _deltaTime) = 0; // TODO: Pass mouse movement
        virtual void onMousePressed(const MouseClickedInputMessage& _msMsg, float _deltaTime) = 0;
    protected:

        bool m_bUseKeyboard         : 1;
        bool m_bUseMouseMovement    : 1;
        bool m_bUseMouseButtons     : 1;
        bool m_bUseController       : 1; // That won't be done before a while
    };
}

#endif //TUTORIAL_INPUTLISTENER_H
