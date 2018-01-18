//
// Created by notjustin on 1/17/18.
//

#ifndef VAPEENGINE_RIGIDBODYCOMPONENT_H
#define VAPEENGINE_RIGIDBODYCOMPONENT_H

#include <patterns/Component.h>

class RigidBodyComponent : public Component {
public:
    explicit RigidBodyComponent(Component* _parent) : Component(_parent), m_fGravityScale(1.f) {}

    float m_fGravityScale;

    bool m_bLockMovementX   : 1;
    bool m_bLockMovementY   : 1;
    bool m_bLockMovementZ   : 1;
    bool m_bLockRotationX   : 1;
    bool m_bLockRotationY   : 1;
    bool m_bLockRotationZ   : 1;

    /*
     * TODO: physics stuff
     */
};


#endif //VAPEENGINE_RIGIDBODYCOMPONENT_H
