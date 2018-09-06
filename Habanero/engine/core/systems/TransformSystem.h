//
// Created by l3gume on 19/02/18.
//
#pragma once
#ifndef VAPEENGINE_TRANSFORMSYSTEM_H
#define VAPEENGINE_TRANSFORMSYSTEM_H

#include "engine/core/ecs/ecs.h"

using namespace ecs;

class TransformSystem : public System {
    friend class SystemManager;
public:
    TransformSystem() : System() {
#if EDITOR
        m_enabledInEditorMode = true;
#endif
    }

private:
    void update(float _deltaTime) override;
};


#endif //VAPEENGINE_TRANSFORMSYSTEM_H
