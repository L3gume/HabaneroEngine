//
// Created by l3gume on 23/02/18.
//
#ifndef VAPEENGINE_BOXCOLLIDERCOMPONENT_H
#define VAPEENGINE_BOXCOLLIDERCOMPONENT_H

#include <ecs/ecs.h>
#include <physics/AABB.h>

using namespace ECS;

struct BoxColliderComponent : Component {
    BoxColliderComponent(const glm::vec3& _center, const glm::vec3& _halfWidths) {
        collider = AABB(_center, _halfWidths);
    }

    AABB collider; 
    bool isTrigger = false;
    bool isStatic = false;
};

#endif //VAPEENGINE_BOXCOLLIDERCOMPONENT_H
