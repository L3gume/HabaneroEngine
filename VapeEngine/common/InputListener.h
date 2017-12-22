//
// Created by notjustin on 12/22/17.
//

#ifndef TUTORIAL_INPUTLISTENER_H
#define TUTORIAL_INPUTLISTENER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

//
// Interface for listeners (Abstract class)
//
class InputListener {
public:
    InputListener();
    ~InputListener(); // TODO: This will have to go update the inputManager's listener list.

protected:
    /* These methods have to be overridden by the derived listeners */
    virtual void onKeyPressed() = 0; // TODO: Setup a way to pass around inputs, probably an InputEvent struct or just an array of GLFW keycodes
    virtual void onMouseMoved() = 0; // TODO: Pass mouse movement
    virtual void onMousePressed() = 0;
};


#endif //TUTORIAL_INPUTLISTENER_H
