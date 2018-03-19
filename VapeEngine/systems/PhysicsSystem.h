#ifndef VAPEENGINE_PHYSICSSYSTEM_H
#define VAPEENGINE_PHYSICSSYSTEM_H

#include <ecs/ecs.h>
#include <core/Engine.h>
#include <components/TransformComponent.h>
#include <components/RigidBodyComponent.h>
#include <components/ColliderComponent.h>
#include <glm/glm.hpp>
#include <vector>
#include <common/util.h>
#include <physics/VapePhysics.h>

using namespace ECS;

class PhysicsSystem : public System {
    friend class SystemManager;
public:
    PhysicsSystem() : System() {
#if EDITOR 
        m_enabledInEditorMode = false;
#endif 
    }
    
private:
    std::vector<Entity*> m_entities;
    
    void preUpdate(float _deltaTime) override;
    void update(float _deltaTime) override;
};

#endif
