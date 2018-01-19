//
// Created by notjustin on 12/31/17.
//
#include "GameObject.h"

using namespace Core;

void GameObject::update(const float _deltaTime) {
    if (m_parent) {
        if (instanceOf<GameObject>(m_parent)) {
            // Update the current object's transform relative to the parent's transform.
            Transform* parentTransform = static_cast<GameObject*>(m_parent)->getTransform();
            m_absoluteTransform.position = m_transform.position + parentTransform->position;
            // TODO: Rotations are actually a lot more complicated.
            m_absoluteTransform.rotation = m_transform.rotation + parentTransform->rotation;
            m_absoluteTransform.scale = m_transform.scale + parentTransform->scale;
        }
    }

    /* Add the rest here */
}

// TODO