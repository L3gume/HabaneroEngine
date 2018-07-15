//
// Created by notjustin on 12/22/17.
//

#include <algorithm>
#include "engine/core/logging/LogManager.h"
#include "InputManager.h"

using namespace Input;

void InputManager::init(const HWND _window) {
	// Initialize the keyboard and mouse
	m_pKeyboard = std::make_unique<DirectX::Keyboard>();
	m_pMouse = std::make_unique<DirectX::Mouse>();
	m_pKeyboardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	m_pMouseTracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	
	// Set mouse window and mode
	// Mouse position is relative to window
	m_pMouse->SetWindow(_window);
	m_pMouse->SetMode(DirectX::Mouse::Mode::MODE_RELATIVE);
}

/*
 * Add a listener to the InputManager
 */
bool InputManager::addInputListener(InputListener* _listener) {
    if (!_listener) {
#if _DEBUG 
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::INPUT, VapeLog::LogType::ISSUE,
                VapeLog::LogSeverity::CRITICAL, "Passed input listener is NULL"));
#endif
        return false;
    }

    m_listeners.emplace_back(_listener); // This one's pretty simple.

    return true;
}

/*
 * Removes the pointer from the deque, the object is not deleted from memory.
 */
bool InputManager::removeInputListener(InputListener* _listener) {
    if (!_listener) {
#if _DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::INPUT, VapeLog::LogType::ISSUE,
                VapeLog::LogSeverity::CRITICAL, "Passed input listener is NULL"));
#endif
        return false;
    }

    // Go through the deque of listeners, delete the listener if found
    for (auto it = m_listeners.begin(); it != m_listeners.end(); it++) {
        if (*it == _listener) {
            it = m_listeners.erase(it);
            return true;
        }
    }
    return false;
}

/*
 * TODO: maybe find a way to disable some keys so we don't poll all of them (if it ever is an issue)
 */
void InputManager::update() {
	// Get keyboard state
	auto keyboardState = m_pKeyboard->GetState();
	m_pKeyboardTracker->Update(keyboardState);
	
	// Get mouse state
	auto mouseState = m_pMouse->GetState();
	m_pMouseTracker->Update(mouseState);
	
    KeyboardInputMessage kbdInMsg = getKeyboardInputs(m_pKeyboardTracker.get());
    MouseMovedInputMessage msMvMsg = getMouseCoordinates(m_pMouse.get());
    MouseClickedInputMessage msClkMsg = getMouseInputs(m_pMouseTracker.get());
    //MouseScrolledInputMessage msRlMsg = m_scrolledInputMessage;

    /* Observer Pattern anyone? :D */
    for (InputListener* il : m_listeners) {
        if (il->getUseKeyboard()) {
            //il->onKeyPressed(kbdInMsg);
        }
        if (il->getUseMouseMove()) {
            //il->onMouseMoved(msMvMsg);
        }
        if (il->getUseMouseButtons()) {
            //il->onMousePressed(msClkMsg);
        }
        if (il->getUseMouseWheel()) {
            //il->onMouseScrolled(msRlMsg);
            updateScrollInput(0.0, 0.0);
        }
        if (il->getUseController()) {
#if _DEBUG
            VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                    VapeLog::LogTag::INPUT, VapeLog::LogType::MESSAGE,
                    VapeLog::LogSeverity::LOW, "Controller support is not implemented"));
#endif
        }
    }
}

void InputManager::updateScrollInput(double _x, double _y) {
    m_scrolledInputMessage.m_dXOffset = _x;
    m_scrolledInputMessage.m_dXOffset = _y;
}

/*
 * [Justin]: I feel kinda bad about that one... At least I formatted it in a readable-ish way
 */
KeyboardInputMessage InputManager::getKeyboardInputs(DirectX::Keyboard::KeyboardStateTracker* _tracker) {
    KeyboardInputMessage kbdInMsg = {}; // In theory that should initialize everything to false.
    if (_tracker->pressed.Space)			kbdInMsg.KEY_SPACE         = true;
    if (_tracker->pressed.OemComma)			kbdInMsg.KEY_COMMA         = true;
    if (_tracker->pressed.OemMinus)			kbdInMsg.KEY_MINUS         = true;
    if (_tracker->pressed.OemPeriod)		kbdInMsg.KEY_PERIOD        = true;
    if (_tracker->pressed.OemBackslash)		kbdInMsg.KEY_SLASH         = true;
    if (_tracker->pressed.D0)				kbdInMsg.KEY_0             = true;
    if (_tracker->pressed.D1)				kbdInMsg.KEY_1             = true;
    if (_tracker->pressed.D2)				kbdInMsg.KEY_2             = true;
    if (_tracker->pressed.D3)				kbdInMsg.KEY_3             = true;
    if (_tracker->pressed.D4)				kbdInMsg.KEY_4             = true;
    if (_tracker->pressed.D5)				kbdInMsg.KEY_5             = true;
    if (_tracker->pressed.D6)				kbdInMsg.KEY_6             = true;
    if (_tracker->pressed.D7)				kbdInMsg.KEY_7             = true;
    if (_tracker->pressed.D8)				kbdInMsg.KEY_8             = true;
    if (_tracker->pressed.D9)				kbdInMsg.KEY_9             = true;
    if (_tracker->pressed.OemSemicolon)		kbdInMsg.KEY_SEMICOLON     = true;
    if (_tracker->pressed.A)				kbdInMsg.KEY_A             = true;
    if (_tracker->pressed.B)				kbdInMsg.KEY_B             = true;
    if (_tracker->pressed.C)				kbdInMsg.KEY_C             = true;
    if (_tracker->pressed.D)				kbdInMsg.KEY_D             = true;
    if (_tracker->pressed.E)				kbdInMsg.KEY_E             = true;
    if (_tracker->pressed.F)				kbdInMsg.KEY_F             = true;
    if (_tracker->pressed.G)				kbdInMsg.KEY_G             = true;
    if (_tracker->pressed.H)				kbdInMsg.KEY_H             = true;
    if (_tracker->pressed.I)				kbdInMsg.KEY_I             = true;
    if (_tracker->pressed.J)				kbdInMsg.KEY_J             = true;
    if (_tracker->pressed.K)				kbdInMsg.KEY_K             = true;
    if (_tracker->pressed.L)				kbdInMsg.KEY_L             = true;
    if (_tracker->pressed.M)				kbdInMsg.KEY_M             = true;
    if (_tracker->pressed.N)				kbdInMsg.KEY_N             = true;
    if (_tracker->pressed.O)				kbdInMsg.KEY_O             = true;
    if (_tracker->pressed.P)				kbdInMsg.KEY_P             = true;
    if (_tracker->pressed.Q)				kbdInMsg.KEY_Q             = true;
    if (_tracker->pressed.R)				kbdInMsg.KEY_R             = true;
    if (_tracker->pressed.S)				kbdInMsg.KEY_S             = true;
    if (_tracker->pressed.T)				kbdInMsg.KEY_T             = true;
    if (_tracker->pressed.U)				kbdInMsg.KEY_U             = true;
    if (_tracker->pressed.V)				kbdInMsg.KEY_V             = true;
    if (_tracker->pressed.W)				kbdInMsg.KEY_W             = true;
    if (_tracker->pressed.X)				kbdInMsg.KEY_X             = true;
    if (_tracker->pressed.Y)				kbdInMsg.KEY_Y             = true;
    if (_tracker->pressed.Z)				kbdInMsg.KEY_Z             = true;
    if (_tracker->pressed.Escape)			kbdInMsg.KEY_ESCAPE        = true;
    if (_tracker->pressed.Enter)			kbdInMsg.KEY_ENTER         = true;
    if (_tracker->pressed.Tab)				kbdInMsg.KEY_TAB           = true;
    if (_tracker->pressed.Back)				kbdInMsg.KEY_BACKSPACE     = true;
    if (_tracker->pressed.Insert)			kbdInMsg.KEY_INSERT        = true;
    if (_tracker->pressed.Delete)			kbdInMsg.KEY_DELETE        = true;
    if (_tracker->pressed.Right)			kbdInMsg.KEY_RIGHT         = true;
    if (_tracker->pressed.Left)				kbdInMsg.KEY_LEFT          = true;
    if (_tracker->pressed.Down)				kbdInMsg.KEY_DOWN          = true;
    if (_tracker->pressed.Up)				kbdInMsg.KEY_UP            = true;
    if (_tracker->pressed.PageUp)			kbdInMsg.KEY_PAGE_UP       = true;
    if (_tracker->pressed.PageDown)			kbdInMsg.KEY_PAGE_DOWN     = true;
    if (_tracker->pressed.Home)				kbdInMsg.KEY_HOME          = true;
    if (_tracker->pressed.End)				kbdInMsg.KEY_END           = true;
    if (_tracker->pressed.CapsLock)			kbdInMsg.KEY_CAPS_LOCK     = true;
    if (_tracker->pressed.NumLock)			kbdInMsg.KEY_NUM_LOCK      = true;
    if (_tracker->pressed.PrintScreen)		kbdInMsg.KEY_PRINT_SCREEN  = true;
    if (_tracker->pressed.Pause)			kbdInMsg.KEY_PAUSE         = true;
    if (_tracker->pressed.F1)				kbdInMsg.KEY_F1            = true;
    if (_tracker->pressed.F2)				kbdInMsg.KEY_F2            = true;
    if (_tracker->pressed.F3)				kbdInMsg.KEY_F3            = true;
    if (_tracker->pressed.F4)				kbdInMsg.KEY_F4            = true;
    if (_tracker->pressed.F5)				kbdInMsg.KEY_F5            = true;
    if (_tracker->pressed.F6)				kbdInMsg.KEY_F6            = true;
    if (_tracker->pressed.F7)				kbdInMsg.KEY_F7            = true;
    if (_tracker->pressed.F8)				kbdInMsg.KEY_F8            = true;
    if (_tracker->pressed.F9)				kbdInMsg.KEY_F9            = true;
    if (_tracker->pressed.F10)				kbdInMsg.KEY_F10           = true;
    if (_tracker->pressed.F11)				kbdInMsg.KEY_F11           = true;
    if (_tracker->pressed.F12)				kbdInMsg.KEY_F12           = true;
    if (_tracker->pressed.NumPad0)			kbdInMsg.KEY_KP_0          = true;
    if (_tracker->pressed.NumPad1)			kbdInMsg.KEY_KP_1          = true;
    if (_tracker->pressed.NumPad2)			kbdInMsg.KEY_KP_2          = true;
	if (_tracker->pressed.NumPad3)			kbdInMsg.KEY_KP_3          = true;
    if (_tracker->pressed.NumPad4)			kbdInMsg.KEY_KP_4          = true;
    if (_tracker->pressed.NumPad5)			kbdInMsg.KEY_KP_5          = true;
    if (_tracker->pressed.NumPad6)			kbdInMsg.KEY_KP_6          = true;
    if (_tracker->pressed.NumPad7)			kbdInMsg.KEY_KP_7          = true;
    if (_tracker->pressed.NumPad8)			kbdInMsg.KEY_KP_8          = true;
    if (_tracker->pressed.NumPad9)			kbdInMsg.KEY_KP_9          = true;
    if (_tracker->pressed.Decimal)			kbdInMsg.KEY_KP_DECIMAL    = true;
    if (_tracker->pressed.Divide)			kbdInMsg.KEY_KP_DIVIDE     = true;
    if (_tracker->pressed.Multiply)			kbdInMsg.KEY_KP_MULTIPLY   = true;
    if (_tracker->pressed.Subtract)			kbdInMsg.KEY_KP_SUBTRACT   = true;
    if (_tracker->pressed.Add)				kbdInMsg.KEY_KP_ADD        = true;
    if (_tracker->pressed.LeftShift)		kbdInMsg.KEY_LEFT_SHIFT    = true;
    if (_tracker->pressed.LeftControl)		kbdInMsg.KEY_LEFT_CONTROL  = true;
    if (_tracker->pressed.LeftAlt)			kbdInMsg.KEY_LEFT_ALT      = true;
    if (_tracker->pressed.LeftWindows)		kbdInMsg.KEY_LEFT_SUPER    = true;
    if (_tracker->pressed.RightShift)		kbdInMsg.KEY_RIGHT_SHIFT   = true;
    if (_tracker->pressed.RightControl)		kbdInMsg.KEY_RIGHT_CONTROL = true;
    if (_tracker->pressed.RightAlt)			kbdInMsg.KEY_RIGHT_ALT     = true;
    if (_tracker->pressed.RightWindows)		kbdInMsg.KEY_RIGHT_SUPER   = true;

    return kbdInMsg;
}

MouseMovedInputMessage InputManager::getMouseCoordinates(DirectX::Mouse* _mouse) {
    MouseMovedInputMessage msMsg = {};
	auto state = _mouse->GetState();
	msMsg.m_dXPos = state.x;
	msMsg.m_dYPos = state.y;
    return msMsg;
}

MouseClickedInputMessage InputManager::getMouseInputs(DirectX::Mouse::ButtonStateTracker* _tracker) {
    MouseClickedInputMessage msMsg = {};
    if (_tracker->leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)   msMsg.MOUSE_BUTTON_1 = true;
    if (_tracker->rightButton == DirectX::Mouse::ButtonStateTracker::PRESSED)  msMsg.MOUSE_BUTTON_2 = true;
    if (_tracker->middleButton == DirectX::Mouse::ButtonStateTracker::PRESSED) msMsg.MOUSE_BUTTON_3 = true;

    return msMsg;
}