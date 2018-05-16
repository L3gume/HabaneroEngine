//
// Created by l3gume on 12/02/18.
//
#pragma once
#ifndef HABANERO_SCRIPTCOMPONENT_H
#define HABANERO_SCRIPTCOMPONENT_H


// TODO: CHANGE THIS


#include "../ecs/ecs.h"

/*
 * ScriptComponents will hold an object of type script, which contains logic.
 * The script itself will know what entity it belongs to so it it will be able to do stuff to it.
 */
class Script {
    friend class ScriptSystem;
public:
    Script() = default;

    // member functions that are meant to be overridden
    virtual void init();
    virtual void preUpdate(float _deltaTime) {}
    virtual void update(float _deltaTime) {}
    virtual void postUpdate(float _deltaTime) {}

    std::string m_sName;
protected:
    ECS::Entity* m_entity = nullptr;
};

/*
 * Heavily inspired from Unity's scripting system.
 */
struct ScriptComponent : ECS::Component {
    explicit ScriptComponent(Script* _script) {
        std::unique_ptr<Script> uPtr{_script};
        m_script = std::move(uPtr);
    }
    std::unique_ptr<Script> m_script;
    bool initialized = false;
};

#endif //HABANERO_SCRIPTCOMPONENT_H
