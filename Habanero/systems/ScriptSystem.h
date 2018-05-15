//
// Created by l3gume on 12/02/18.
//

#ifndef VAPEENGINE_SCRIPTSYSTEM_H
#define VAPEENGINE_SCRIPTSYSTEM_H

#include "../ecs/ecs.h"
#include "../core/Engine.h"
#include "../components/ScriptComponent.h"

using namespace ECS;

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
