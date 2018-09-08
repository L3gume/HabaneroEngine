//
// Created by l3gume on 12/02/18.
//
#pragma once
#ifndef VAPEENGINE_SCRIPTSYSTEM_H
#define VAPEENGINE_SCRIPTSYSTEM_H

#include "engine/core/ecs/ecs.h"
#include "engine/core/Engine.h"
#include "engine/core/components/ScriptComponent.h"

using namespace ecs;

class ScriptSystem : public System {
friend class SystemManager;
public:
    ScriptSystem() {
#if EDITOR
        m_enabledInEditorMode = false;
#endif
    }

private:
    void preUpdate(float _deltaTime) override;
    void update(float _deltaTime) override;

    std::vector<Entity*> m_scriptedEntities;
};


#endif //VAPEENGINE_SCRIPTSYSTEM_H
