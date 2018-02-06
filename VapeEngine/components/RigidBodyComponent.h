//
// Created by notjustin on 1/17/18.
//

#ifndef VAPEENGINE_RIGIDBODYCOMPONENT_H
#define VAPEENGINE_RIGIDBODYCOMPONENT_H

#include <core/GameObject.h>

#if EDITOR

#include <imgui/imgui.h>

#endif

class RigidBodyComponent : public Component {
public:
    explicit RigidBodyComponent(Core::GameObject *_parent)
            : Component(_parent), m_fGravityScale(1.f),
              m_bLockMovementX(false), m_bLockMovementY(false),
              m_bLockMovementZ(false), m_bLockRotationX(false),
              m_bLockRotationY(false), m_bLockRotationZ(false),
              m_bKinematic(false) {}

    float m_fGravityScale;

    bool m_bLockMovementX;
    bool m_bLockMovementY;
    bool m_bLockMovementZ;
    bool m_bLockRotationX;
    bool m_bLockRotationY;
    bool m_bLockRotationZ;
    bool m_bKinematic; // Not affected by physics

#if EDITOR

    virtual void renderInspectorSection() override;

#endif

    /*
     * TODO: physics stuff
     */
};


#endif //VAPEENGINE_RIGIDBODYCOMPONENT_H
