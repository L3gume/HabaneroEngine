//
// Created by notjustin on 2/22/18.
//

#include <glm/gtc/quaternion.hpp>
#include <common/quatUtils.h>
#include "LookAtScript.h"

void LookAtScript::init() {
    Script::init();
    assert(m_entity->hasComponent<TransformComponent>());
    transform = &m_entity->getComponent<TransformComponent>();

    assert(m_entity->getParent() && m_entity->getParent()->hasComponent<TransformComponent>());
    parentTransform = &m_entity->getParent()->getComponent<TransformComponent>();
}

void LookAtScript::update(float _deltaTime) {

}
