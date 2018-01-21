//
// Created by notjustin on 12/31/17.
//
#include "GameObject.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace Core;

void GameObject::update(const float _deltaTime) {
    if (m_parent) {
        if (instanceOf<GameObject>(m_parent)) {
            // Update the current object's transform relative to the parent's transform.
            Transform* parentTransform = static_cast<GameObject*>(m_parent)->getTransform();

            m_absoluteTransform.rotation = parentTransform->rotation;
            m_absoluteTransform.position = parentTransform->position +
                    (glm::quat(m_absoluteTransform.rotation) * (m_transform.position)) ;
            m_absoluteTransform.scale = m_transform.scale + parentTransform->scale;
        }
    }

    /* Add the rest here */
}

// TODO