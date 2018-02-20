//
// Created by l3gume on 12/02/18.
//


#include "ScriptSystem.h"

void ScriptSystem::preUpdate(float _deltaTime) {
    m_scriptedEntities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
            getComponentTypeID<ScriptComponent>());

    for (auto& ent : m_scriptedEntities) {
        auto& comp = ent->getComponent<ScriptComponent>();
        if (!comp.initialized) {
            assert(comp.m_script != nullptr);
            comp.m_script->m_entity = ent;
            comp.m_script->init();
        }
        comp.m_script->preUpdate(_deltaTime);
    }
}

void ScriptSystem::update(float _deltaTime) {
    for (auto& ent : m_scriptedEntities) {
        auto& comp = ent->getComponent<ScriptComponent>();
        comp.m_script->update(_deltaTime);
    }
}

