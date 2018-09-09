//
// Created by notjustin on 12/23/17.
//
#pragma once
#ifndef HABANERO_INPUTMESSAGE_H
#define HABANERO_INPUTMESSAGE_H

namespace input {
/* Heard you liked bitmaps ;) */
struct KeyboardInputMessage {
    bool KEY_SPACE          : 1;
    bool KEY_APOSTROPHE     : 1;
    bool KEY_COMMA          : 1;
    bool KEY_MINUS          : 1;
    bool KEY_PERIOD         : 1;
    bool KEY_SLASH          : 1;
    bool KEY_0              : 1;
    bool KEY_1              : 1;
    bool KEY_2              : 1;
    bool KEY_3              : 1;
    bool KEY_4              : 1;
    bool KEY_5              : 1;
    bool KEY_6              : 1;
    bool KEY_7              : 1;
    bool KEY_8              : 1;
    bool KEY_9              : 1;
    bool KEY_SEMICOLON      : 1;
    bool KEY_EQUAL          : 1;
    bool KEY_A              : 1;
    bool KEY_B              : 1;
    bool KEY_C              : 1;
    bool KEY_D              : 1;
    bool KEY_E              : 1;
    bool KEY_F              : 1;
    bool KEY_G              : 1;
    bool KEY_H              : 1;
    bool KEY_I              : 1;
    bool KEY_J              : 1;
    bool KEY_K              : 1;
    bool KEY_L              : 1;
    bool KEY_M              : 1;
    bool KEY_N              : 1;
    bool KEY_O              : 1;
    bool KEY_P              : 1;
    bool KEY_Q              : 1;
    bool KEY_R              : 1;
    bool KEY_S              : 1;
    bool KEY_T              : 1;
    bool KEY_U              : 1;
    bool KEY_V              : 1;
    bool KEY_W              : 1;
    bool KEY_X              : 1;
    bool KEY_Y              : 1;
    bool KEY_Z              : 1;
    bool KEY_LEFT_BRACKET   : 1;
    bool KEY_BACKSLASH      : 1;
    bool KEY_RIGHT_BRACKET  : 1;
    bool KEY_GRAVE_ACCENT   : 1;
    bool KEY_WORLD_1        : 1;
    bool KEY_WORLD_2        : 1;
    bool KEY_ESCAPE         : 1;
    bool KEY_ENTER          : 1;
    bool KEY_TAB            : 1;
    bool KEY_BACKSPACE      : 1;
    bool KEY_INSERT         : 1;
    bool KEY_DELETE         : 1;
    bool KEY_RIGHT          : 1;
    bool KEY_LEFT           : 1;
    bool KEY_DOWN           : 1;
    bool KEY_UP             : 1;
    bool KEY_PAGE_UP        : 1;
    bool KEY_PAGE_DOWN      : 1;
    bool KEY_HOME           : 1;
    bool KEY_END            : 1;
    bool KEY_CAPS_LOCK      : 1;
    bool KEY_SCROLL_LOCK    : 1;
    bool KEY_NUM_LOCK       : 1;
    bool KEY_PRINT_SCREEN   : 1;
    bool KEY_PAUSE          : 1;
    bool KEY_F1             : 1;
    bool KEY_F2             : 1;
    bool KEY_F3             : 1;
    bool KEY_F4             : 1;
    bool KEY_F5             : 1;
    bool KEY_F6             : 1;
    bool KEY_F7             : 1;
    bool KEY_F8             : 1;
    bool KEY_F9             : 1;
    bool KEY_F10            : 1;
    bool KEY_F11            : 1;
    bool KEY_F12            : 1;
    bool KEY_F13            : 1;
    bool KEY_F14            : 1;
    bool KEY_F15            : 1;
    bool KEY_F16            : 1;
    bool KEY_F17            : 1;
    bool KEY_F18            : 1;
    bool KEY_F19            : 1;
    bool KEY_F20            : 1;
    bool KEY_F21            : 1;
    bool KEY_F22            : 1;
    bool KEY_F23            : 1;
    bool KEY_F24            : 1;
    bool KEY_F25            : 1;
    bool KEY_KP_0           : 1;
    bool KEY_KP_1           : 1;
    bool KEY_KP_2           : 1;
    bool KEY_KP_3           : 1;
    bool KEY_KP_4           : 1;
    bool KEY_KP_5           : 1;
    bool KEY_KP_6           : 1;
    bool KEY_KP_7           : 1;
    bool KEY_KP_8           : 1;
    bool KEY_KP_9           : 1;
    bool KEY_KP_DECIMAL     : 1;
    bool KEY_KP_DIVIDE      : 1;
    bool KEY_KP_MULTIPLY    : 1;
    bool KEY_KP_SUBTRACT    : 1;
    bool KEY_KP_ADD         : 1;
    bool KEY_KP_ENTER       : 1;
    bool KEY_KP_EQUAL       : 1;
    bool KEY_LEFT_SHIFT     : 1;
    bool KEY_LEFT_CONTROL   : 1;
    bool KEY_LEFT_ALT       : 1;
    bool KEY_LEFT_SUPER     : 1;
    bool KEY_RIGHT_SHIFT    : 1;
    bool KEY_RIGHT_CONTROL  : 1;
    bool KEY_RIGHT_ALT      : 1;
    bool KEY_RIGHT_SUPER    : 1;
    bool KEY_MENU           : 1;
};

struct MouseMovedInputMessage {
    double m_dXPos = 0.0;
    double m_dYPos = 0.0;
};

struct MouseClickedInputMessage {
    bool MOUSE_BUTTON_1      : 1;
    bool MOUSE_BUTTON_2      : 1;
    bool MOUSE_BUTTON_3      : 1;
    bool MOUSE_BUTTON_4      : 1;
    bool MOUSE_BUTTON_5      : 1;
    bool MOUSE_BUTTON_6      : 1;
    bool MOUSE_BUTTON_7      : 1;
    bool MOUSE_BUTTON_8      : 1;
    bool MOUSE_BUTTON_LAST   : 1;
    bool MOUSE_BUTTON_LEFT   : 1;
    bool MOUSE_BUTTON_RIGHT  : 1;
    bool MOUSE_BUTTON_MIDDLE : 1;
};

struct MouseScrolledInputMessage {
    double m_dXOffset = 0.0;
    double m_dYOffset = 0.0;
};
} // namespace input

#endif //HABANERO_INPUTMESSAGE_H
