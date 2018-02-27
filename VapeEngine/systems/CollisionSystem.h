//
// Created by l3gume on 26/02/18.
//

#ifndef VAPEENGINE_COLLISIONSYSTEM_H
#define VAPEENGINE_COLLISIONSYSTEM_H

#include <ecs.h>
#include <core/Engine.h>
#include <components/BoxColliderComponent.h>
#include <components/CollisionHandlerComponent.h>
#include <components/TransformComponent.h>

using namespace ECS;

class CollisionSystem : public System {
    friend class SystemManager;
public:
    CollisionSystem() : System() {
#if EDITOR
        m_enabledInEditorMode = false;
#endif
    }

private:
    void update(float _deltaTime) override;
    bool testAABBCollision(Entity* e1, Entity* e2, Collision& col);
};


#endif //VAPEENGINE_COLLISIONSYSTEM_H
