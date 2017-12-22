//
// Created by notjustin on 12/22/17.
//

#ifndef TUTORIAL_INPUTMANAGER_H
#define TUTORIAL_INPUTMANAGER_H

#include <deque>
#include "InputListener.h"

//
// Input Manager, implemented as a singleton since we only really want one.
// Options: 1) have the systems poll the input manager and do their own thing 2) have systems implement the inputlistener
// interface (or inherit from an inputlistener class and have the inputs be pushed by the manager to each system.
//
class InputManager {
public:
    static InputManager& getInstance() {
        static InputManager instance; // Guaranteed to be destroyed.
        return instance;
    }
    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;

    void addInputListener(InputListener* _listener);
private:
    InputManager() = default; // Constructor kept private since this is a singleton

    std::deque<InputListener*> m_listeners; // List of input listeners
};


#endif //TUTORIAL_INPUTMANAGER_H
