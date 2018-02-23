//
// Created by notjustin on 12/22/17.
//

#include <algorithm>
#include "LogManager.h"
#include "InputManager.h"

using namespace VapeInput;

void InputManager::init(GLFWwindow* _window) {
    // Not entirely sure about this part, will probably have to be refactored at some point
    glfwSetScrollCallback(_window, [](GLFWwindow* _window, double _x, double _y) {
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::INPUT, VapeLog::LogType::MESSAGE,
                VapeLog::LogSeverity::CRITICAL, "Mouse wheel scrolled!"));
#endif
        InputManager::getInstance().updateScrollInput(_x, _y);
    });
}

/*
 * Add a listener to the InputManager
 */
bool InputManager::addInputListener(InputListener* _listener) {
    if (!_listener) {
#ifdef DEBUG
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
#if DEBUG
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
void InputManager::update(GLFWwindow* _window, float _deltaTime) {
    KeyboardInputMessage kbdInMsg = getKeyboardInputs(_window);
    MouseMovedInputMessage msMvMsg = getMouseCoordinates(_window);
    MouseClickedInputMessage msClkMsg = getMouseInputs(_window);
    MouseScrolledInputMessage msRlMsg = m_scrolledInputMessage;

    /* Observer Pattern anyone? :D */
    for (InputListener* il : m_listeners) {
        if (il->getUseKeyboard()) {
            il->onKeyPressed(kbdInMsg);
        }
        if (il->getUseMouseMove()) {
            il->onMouseMoved(msMvMsg);
        }
        if (il->getUseMouseButtons()) {
            il->onMousePressed(msClkMsg);
        }
        if (il->getUseMouseWheel()) {
            il->onMouseScrolled(msRlMsg);
            updateScrollInput(0.0, 0.0);
        }
        if (il->getUseController()) {
#if DEBUG
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
KeyboardInputMessage InputManager::getKeyboardInputs(GLFWwindow* _window) {
    KeyboardInputMessage kbdInMsg = {}; // In theory that should initialize everything to false.
    if (glfwGetKey(_window, GLFW_KEY_SPACE        ) == GLFW_PRESS) kbdInMsg.KEY_SPACE         = true;
    if (glfwGetKey(_window, GLFW_KEY_APOSTROPHE   ) == GLFW_PRESS) kbdInMsg.KEY_APOSTROPHE    = true;
    if (glfwGetKey(_window, GLFW_KEY_COMMA        ) == GLFW_PRESS) kbdInMsg.KEY_COMMA         = true;
    if (glfwGetKey(_window, GLFW_KEY_MINUS        ) == GLFW_PRESS) kbdInMsg.KEY_MINUS         = true;
    if (glfwGetKey(_window, GLFW_KEY_PERIOD       ) == GLFW_PRESS) kbdInMsg.KEY_PERIOD        = true;
    if (glfwGetKey(_window, GLFW_KEY_SLASH        ) == GLFW_PRESS) kbdInMsg.KEY_SLASH         = true;
    if (glfwGetKey(_window, GLFW_KEY_0            ) == GLFW_PRESS) kbdInMsg.KEY_0             = true;
    if (glfwGetKey(_window, GLFW_KEY_1            ) == GLFW_PRESS) kbdInMsg.KEY_1             = true;
    if (glfwGetKey(_window, GLFW_KEY_2            ) == GLFW_PRESS) kbdInMsg.KEY_2             = true;
    if (glfwGetKey(_window, GLFW_KEY_3            ) == GLFW_PRESS) kbdInMsg.KEY_3             = true;
    if (glfwGetKey(_window, GLFW_KEY_4            ) == GLFW_PRESS) kbdInMsg.KEY_4             = true;
    if (glfwGetKey(_window, GLFW_KEY_5            ) == GLFW_PRESS) kbdInMsg.KEY_5             = true;
    if (glfwGetKey(_window, GLFW_KEY_6            ) == GLFW_PRESS) kbdInMsg.KEY_6             = true;
    if (glfwGetKey(_window, GLFW_KEY_7            ) == GLFW_PRESS) kbdInMsg.KEY_7             = true;
    if (glfwGetKey(_window, GLFW_KEY_8            ) == GLFW_PRESS) kbdInMsg.KEY_8             = true;
    if (glfwGetKey(_window, GLFW_KEY_9            ) == GLFW_PRESS) kbdInMsg.KEY_9             = true;
    if (glfwGetKey(_window, GLFW_KEY_SEMICOLON    ) == GLFW_PRESS) kbdInMsg.KEY_SEMICOLON     = true;
    if (glfwGetKey(_window, GLFW_KEY_EQUAL        ) == GLFW_PRESS) kbdInMsg.KEY_EQUAL         = true;
    if (glfwGetKey(_window, GLFW_KEY_A            ) == GLFW_PRESS) kbdInMsg.KEY_A             = true;
    if (glfwGetKey(_window, GLFW_KEY_B            ) == GLFW_PRESS) kbdInMsg.KEY_B             = true;
    if (glfwGetKey(_window, GLFW_KEY_C            ) == GLFW_PRESS) kbdInMsg.KEY_C             = true;
    if (glfwGetKey(_window, GLFW_KEY_D            ) == GLFW_PRESS) kbdInMsg.KEY_D             = true;
    if (glfwGetKey(_window, GLFW_KEY_E            ) == GLFW_PRESS) kbdInMsg.KEY_E             = true;
    if (glfwGetKey(_window, GLFW_KEY_F            ) == GLFW_PRESS) kbdInMsg.KEY_F             = true;
    if (glfwGetKey(_window, GLFW_KEY_G            ) == GLFW_PRESS) kbdInMsg.KEY_G             = true;
    if (glfwGetKey(_window, GLFW_KEY_H            ) == GLFW_PRESS) kbdInMsg.KEY_H             = true;
    if (glfwGetKey(_window, GLFW_KEY_I            ) == GLFW_PRESS) kbdInMsg.KEY_I             = true;
    if (glfwGetKey(_window, GLFW_KEY_J            ) == GLFW_PRESS) kbdInMsg.KEY_J             = true;
    if (glfwGetKey(_window, GLFW_KEY_K            ) == GLFW_PRESS) kbdInMsg.KEY_K             = true;
    if (glfwGetKey(_window, GLFW_KEY_L            ) == GLFW_PRESS) kbdInMsg.KEY_L             = true;
    if (glfwGetKey(_window, GLFW_KEY_M            ) == GLFW_PRESS) kbdInMsg.KEY_M             = true;
    if (glfwGetKey(_window, GLFW_KEY_N            ) == GLFW_PRESS) kbdInMsg.KEY_N             = true;
    if (glfwGetKey(_window, GLFW_KEY_O            ) == GLFW_PRESS) kbdInMsg.KEY_O             = true;
    if (glfwGetKey(_window, GLFW_KEY_P            ) == GLFW_PRESS) kbdInMsg.KEY_P             = true;
    if (glfwGetKey(_window, GLFW_KEY_Q            ) == GLFW_PRESS) kbdInMsg.KEY_Q             = true;
    if (glfwGetKey(_window, GLFW_KEY_R            ) == GLFW_PRESS) kbdInMsg.KEY_R             = true;
    if (glfwGetKey(_window, GLFW_KEY_S            ) == GLFW_PRESS) kbdInMsg.KEY_S             = true;
    if (glfwGetKey(_window, GLFW_KEY_T            ) == GLFW_PRESS) kbdInMsg.KEY_T             = true;
    if (glfwGetKey(_window, GLFW_KEY_U            ) == GLFW_PRESS) kbdInMsg.KEY_U             = true;
    if (glfwGetKey(_window, GLFW_KEY_V            ) == GLFW_PRESS) kbdInMsg.KEY_V             = true;
    if (glfwGetKey(_window, GLFW_KEY_W            ) == GLFW_PRESS) kbdInMsg.KEY_W             = true;
    if (glfwGetKey(_window, GLFW_KEY_X            ) == GLFW_PRESS) kbdInMsg.KEY_X             = true;
    if (glfwGetKey(_window, GLFW_KEY_Y            ) == GLFW_PRESS) kbdInMsg.KEY_Y             = true;
    if (glfwGetKey(_window, GLFW_KEY_Z            ) == GLFW_PRESS) kbdInMsg.KEY_Z             = true;
    if (glfwGetKey(_window, GLFW_KEY_LEFT_BRACKET ) == GLFW_PRESS) kbdInMsg.KEY_LEFT_BRACKET  = true;
    if (glfwGetKey(_window, GLFW_KEY_BACKSLASH    ) == GLFW_PRESS) kbdInMsg.KEY_BACKSLASH     = true;
    if (glfwGetKey(_window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) kbdInMsg.KEY_RIGHT_BRACKET = true;
    if (glfwGetKey(_window, GLFW_KEY_GRAVE_ACCENT ) == GLFW_PRESS) kbdInMsg.KEY_GRAVE_ACCENT  = true;
    if (glfwGetKey(_window, GLFW_KEY_WORLD_1      ) == GLFW_PRESS) kbdInMsg.KEY_WORLD_1       = true;
    if (glfwGetKey(_window, GLFW_KEY_WORLD_2      ) == GLFW_PRESS) kbdInMsg.KEY_WORLD_2       = true;
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE       ) == GLFW_PRESS) kbdInMsg.KEY_ESCAPE        = true;
    if (glfwGetKey(_window, GLFW_KEY_ENTER        ) == GLFW_PRESS) kbdInMsg.KEY_ENTER         = true;
    if (glfwGetKey(_window, GLFW_KEY_TAB          ) == GLFW_PRESS) kbdInMsg.KEY_TAB           = true;
    if (glfwGetKey(_window, GLFW_KEY_BACKSPACE    ) == GLFW_PRESS) kbdInMsg.KEY_BACKSPACE     = true;
    if (glfwGetKey(_window, GLFW_KEY_INSERT       ) == GLFW_PRESS) kbdInMsg.KEY_INSERT        = true;
    if (glfwGetKey(_window, GLFW_KEY_DELETE       ) == GLFW_PRESS) kbdInMsg.KEY_DELETE        = true;
    if (glfwGetKey(_window, GLFW_KEY_RIGHT        ) == GLFW_PRESS) kbdInMsg.KEY_RIGHT         = true;
    if (glfwGetKey(_window, GLFW_KEY_LEFT         ) == GLFW_PRESS) kbdInMsg.KEY_LEFT          = true;
    if (glfwGetKey(_window, GLFW_KEY_DOWN         ) == GLFW_PRESS) kbdInMsg.KEY_DOWN          = true;
    if (glfwGetKey(_window, GLFW_KEY_UP           ) == GLFW_PRESS) kbdInMsg.KEY_UP            = true;
    if (glfwGetKey(_window, GLFW_KEY_PAGE_UP      ) == GLFW_PRESS) kbdInMsg.KEY_PAGE_UP       = true;
    if (glfwGetKey(_window, GLFW_KEY_PAGE_DOWN    ) == GLFW_PRESS) kbdInMsg.KEY_PAGE_DOWN     = true;
    if (glfwGetKey(_window, GLFW_KEY_HOME         ) == GLFW_PRESS) kbdInMsg.KEY_HOME          = true;
    if (glfwGetKey(_window, GLFW_KEY_END          ) == GLFW_PRESS) kbdInMsg.KEY_END           = true;
    if (glfwGetKey(_window, GLFW_KEY_CAPS_LOCK    ) == GLFW_PRESS) kbdInMsg.KEY_CAPS_LOCK     = true;
    if (glfwGetKey(_window, GLFW_KEY_SCROLL_LOCK  ) == GLFW_PRESS) kbdInMsg.KEY_SCROLL_LOCK   = true;
    if (glfwGetKey(_window, GLFW_KEY_NUM_LOCK     ) == GLFW_PRESS) kbdInMsg.KEY_NUM_LOCK      = true;
    if (glfwGetKey(_window, GLFW_KEY_PRINT_SCREEN ) == GLFW_PRESS) kbdInMsg.KEY_PRINT_SCREEN  = true;
    if (glfwGetKey(_window, GLFW_KEY_PAUSE        ) == GLFW_PRESS) kbdInMsg.KEY_PAUSE         = true;
    if (glfwGetKey(_window, GLFW_KEY_F1           ) == GLFW_PRESS) kbdInMsg.KEY_F1            = true;
    if (glfwGetKey(_window, GLFW_KEY_F2           ) == GLFW_PRESS) kbdInMsg.KEY_F2            = true;
    if (glfwGetKey(_window, GLFW_KEY_F3           ) == GLFW_PRESS) kbdInMsg.KEY_F3            = true;
    if (glfwGetKey(_window, GLFW_KEY_F4           ) == GLFW_PRESS) kbdInMsg.KEY_F4            = true;
    if (glfwGetKey(_window, GLFW_KEY_F5           ) == GLFW_PRESS) kbdInMsg.KEY_F5            = true;
    if (glfwGetKey(_window, GLFW_KEY_F6           ) == GLFW_PRESS) kbdInMsg.KEY_F6            = true;
    if (glfwGetKey(_window, GLFW_KEY_F7           ) == GLFW_PRESS) kbdInMsg.KEY_F7            = true;
    if (glfwGetKey(_window, GLFW_KEY_F8           ) == GLFW_PRESS) kbdInMsg.KEY_F8            = true;
    if (glfwGetKey(_window, GLFW_KEY_F9           ) == GLFW_PRESS) kbdInMsg.KEY_F9            = true;
    if (glfwGetKey(_window, GLFW_KEY_F10          ) == GLFW_PRESS) kbdInMsg.KEY_F10           = true;
    if (glfwGetKey(_window, GLFW_KEY_F11          ) == GLFW_PRESS) kbdInMsg.KEY_F11           = true;
    if (glfwGetKey(_window, GLFW_KEY_F12          ) == GLFW_PRESS) kbdInMsg.KEY_F12           = true;
    if (glfwGetKey(_window, GLFW_KEY_F13          ) == GLFW_PRESS) kbdInMsg.KEY_F13           = true;
    if (glfwGetKey(_window, GLFW_KEY_F14          ) == GLFW_PRESS) kbdInMsg.KEY_F14           = true;
    if (glfwGetKey(_window, GLFW_KEY_F15          ) == GLFW_PRESS) kbdInMsg.KEY_F15           = true;
    if (glfwGetKey(_window, GLFW_KEY_F16          ) == GLFW_PRESS) kbdInMsg.KEY_F16           = true;
    if (glfwGetKey(_window, GLFW_KEY_F17          ) == GLFW_PRESS) kbdInMsg.KEY_F17           = true;
    if (glfwGetKey(_window, GLFW_KEY_F18          ) == GLFW_PRESS) kbdInMsg.KEY_F18           = true;
    if (glfwGetKey(_window, GLFW_KEY_F19          ) == GLFW_PRESS) kbdInMsg.KEY_F19           = true;
    if (glfwGetKey(_window, GLFW_KEY_F20          ) == GLFW_PRESS) kbdInMsg.KEY_F20           = true;
    if (glfwGetKey(_window, GLFW_KEY_F21          ) == GLFW_PRESS) kbdInMsg.KEY_F21           = true;
    if (glfwGetKey(_window, GLFW_KEY_F22          ) == GLFW_PRESS) kbdInMsg.KEY_F22           = true;
    if (glfwGetKey(_window, GLFW_KEY_F23          ) == GLFW_PRESS) kbdInMsg.KEY_F23           = true;
    if (glfwGetKey(_window, GLFW_KEY_F24          ) == GLFW_PRESS) kbdInMsg.KEY_F24           = true;
    if (glfwGetKey(_window, GLFW_KEY_F25          ) == GLFW_PRESS) kbdInMsg.KEY_F25           = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_0         ) == GLFW_PRESS) kbdInMsg.KEY_KP_0          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_1         ) == GLFW_PRESS) kbdInMsg.KEY_KP_1          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_2         ) == GLFW_PRESS) kbdInMsg.KEY_KP_2          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_3         ) == GLFW_PRESS) kbdInMsg.KEY_KP_3          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_4         ) == GLFW_PRESS) kbdInMsg.KEY_KP_4          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_5         ) == GLFW_PRESS) kbdInMsg.KEY_KP_5          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_6         ) == GLFW_PRESS) kbdInMsg.KEY_KP_6          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_7         ) == GLFW_PRESS) kbdInMsg.KEY_KP_7          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_8         ) == GLFW_PRESS) kbdInMsg.KEY_KP_8          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_9         ) == GLFW_PRESS) kbdInMsg.KEY_KP_9          = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_DECIMAL   ) == GLFW_PRESS) kbdInMsg.KEY_KP_DECIMAL    = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_DIVIDE    ) == GLFW_PRESS) kbdInMsg.KEY_KP_DIVIDE     = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_MULTIPLY  ) == GLFW_PRESS) kbdInMsg.KEY_KP_MULTIPLY   = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_SUBTRACT  ) == GLFW_PRESS) kbdInMsg.KEY_KP_SUBTRACT   = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_ADD       ) == GLFW_PRESS) kbdInMsg.KEY_KP_ADD        = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_ENTER     ) == GLFW_PRESS) kbdInMsg.KEY_KP_ENTER      = true;
    if (glfwGetKey(_window, GLFW_KEY_KP_EQUAL     ) == GLFW_PRESS) kbdInMsg.KEY_KP_EQUAL      = true;
    if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT   ) == GLFW_PRESS) kbdInMsg.KEY_LEFT_SHIFT    = true;
    if (glfwGetKey(_window, GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS) kbdInMsg.KEY_LEFT_CONTROL  = true;
    if (glfwGetKey(_window, GLFW_KEY_LEFT_ALT     ) == GLFW_PRESS) kbdInMsg.KEY_LEFT_ALT      = true;
    if (glfwGetKey(_window, GLFW_KEY_LEFT_SUPER   ) == GLFW_PRESS) kbdInMsg.KEY_LEFT_SUPER    = true;
    if (glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT  ) == GLFW_PRESS) kbdInMsg.KEY_RIGHT_SHIFT   = true;
    if (glfwGetKey(_window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) kbdInMsg.KEY_RIGHT_CONTROL = true;
    if (glfwGetKey(_window, GLFW_KEY_RIGHT_ALT    ) == GLFW_PRESS) kbdInMsg.KEY_LEFT_ALT      = true;
    if (glfwGetKey(_window, GLFW_KEY_RIGHT_SUPER  ) == GLFW_PRESS) kbdInMsg.KEY_RIGHT_SUPER   = true;
    if (glfwGetKey(_window, GLFW_KEY_MENU         ) == GLFW_PRESS) kbdInMsg.KEY_MENU          = true;

    return kbdInMsg;
}

MouseMovedInputMessage InputManager::getMouseCoordinates(GLFWwindow* _window) {
    MouseMovedInputMessage msMsg = {};
    glfwGetCursorPos(_window, &msMsg.m_dXPos, &msMsg.m_dYPos);

    return msMsg;
}

MouseClickedInputMessage InputManager::getMouseInputs(GLFWwindow* _window) {
    MouseClickedInputMessage msMsg = {};
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_1     ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_1      = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_2     ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_2      = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_3     ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_3      = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_4     ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_4      = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_5     ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_5      = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_6     ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_6      = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_7     ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_7      = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_8     ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_8      = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LAST  ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_LAST   = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT  ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_LEFT   = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS) msMsg.MOUSE_BUTTON_RIGHT  = true;
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) msMsg.MOUSE_BUTTON_MIDDLE = true;

    return msMsg;
}

#if EDITOR
void InputManager::switchMode(bool _gameMode) {
    for (auto& il : m_listeners) {
        il->m_enabled = il->m_enabledInEditorMode ? true : _gameMode;
    }
}
#endif
