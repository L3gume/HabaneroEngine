//
// Created by l3gume on 12/02/18.
//

#include "ScriptComponent.h"

void Script::init() {
    auto& comp = m_entity->getComponent<ScriptComponent>();
    comp.initialized = true;
}
