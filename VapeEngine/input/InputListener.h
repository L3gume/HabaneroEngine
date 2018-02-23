//
// Created by notjustin on 12/22/17.
//

#ifndef VAPEENGINE_INPUTLISTENER_H
#define VAPEENGINE_INPUTLISTENER_H

#include <common/VapeGL.h>
#include "InputMessage.h"

namespace VapeInput {
    //
    // Interface for listeners (Abstract class)
    // Since it is abstract and has no method implementation, its header-only
    //
    class InputListener {
        friend class InputManager;
    public:
        InputListener(bool _useKeyboard, bool _useMouseMov, bool _useMouseButtons, bool _useController,
                      bool _useMouseWheel) :
                m_bUseKeyboard(_useKeyboard),
                m_bUseMouseMovement(_useMouseMov),
                m_bUseMouseButtons(_useMouseButtons),
                m_bUseController(_useController),
                m_bUseMouseWheel(_useMouseWheel) {
            // Constructor
        }

        /* For now, responsibility is left to the programmer to delete the listener from the InputManager */
        virtual ~InputListener() = default;
        // Inlining a getter for a simple flag basically saves a function call
        inline bool getUseKeyboard() { return m_bUseKeyboard; }
        inline bool getUseMouseMove() { return m_bUseMouseMovement; }
        inline bool getUseMouseButtons() { return m_bUseMouseButtons; }
        inline bool getUseController() { return m_bUseController; }
        inline bool getUseMouseWheel() { return m_bUseMouseWheel; }

        /* These methods have to be overridden by the derived listeners */
        virtual void onKeyPressed(const KeyboardInputMessage &_kbdMsg) = 0;
        virtual void onMouseMoved(const MouseMovedInputMessage &_msMsg) = 0;
        virtual void onMousePressed(const MouseClickedInputMessage &_msMsg) = 0;
        virtual void onMouseScrolled(const MouseScrolledInputMessage &_msMsg) = 0;

    protected:
        bool m_enabled              : 1;
        bool m_enabledInEditorMode  : 1;
        bool m_bUseKeyboard         : 1;
        bool m_bUseMouseMovement    : 1;
        bool m_bUseMouseButtons     : 1;
        bool m_bUseMouseWheel       : 1;
        bool m_bUseController       : 1; // That won't be done before a while
    };
}

#endif //VAPEENGINE_INPUTLISTENER_H
