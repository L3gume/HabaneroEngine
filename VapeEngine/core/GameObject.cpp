//
// Created by notjustin on 12/31/17.
//
#include <core/GameObject.h>

using namespace Core;

void GameObject::update(const float _deltaTime) {
    if (m_parent) {
        if (instanceOf<GameObject>(m_parent)) {
            // Update the current object's transform relative to the parent's transform.
            Transform* parentTransform = static_cast<GameObject*>(m_parent)->getTransform();

            m_absoluteTransform.euler_rotation = parentTransform->euler_rotation;
            m_absoluteTransform.position = parentTransform->position +
                    (m_absoluteTransform.getQuatRotation() * (m_transform.position)) ;
            m_absoluteTransform.scale = m_transform.scale + parentTransform->scale;
        }
    }

    /* Add the rest here */
}

// TODO