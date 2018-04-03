//
// Created by notjustin on 3/8/18.
//

#ifndef VAPEENGINE_COLLIDERCOMPONENT_H
#define VAPEENGINE_COLLIDERCOMPONENT_H

#include <ecs/ecs.h>
#include <physics/Sphere.h>
#include <physics/AABB.h>
#include <variant>

using namespace ECS;

/*
 * Used to quickly determine the collider type.
 */
enum colType {
    BOX,
    SPHERE
};

/*
 * Collider, declared as a union of the existing collider shapes.
 */
union Collider {
    AABB boxCollider;
    Sphere sphereCollider;

    // Since the types in the union don't have trivial constructors, we need to provide a constructor for the union.
    Collider() { memset(this, 0, sizeof(Collider)); }
};

struct ColliderComponent : Component {
    /*
     * Box Collider constructor
     */
    ColliderComponent(const glm::vec3 &_center, const glm::vec3 &_halfwidths, const bool _trigger = false,
                      const bool _static = false) {
        collider.boxCollider = AABB(_center, _halfwidths);
        isTrigger = _trigger;
        isStatic = _static;
        type = colType::BOX;
    }

    /*
     * Sphere collider constructor
     */
    ColliderComponent(const glm::vec3 &_center, const float _radius, const bool _trigger = false,
                   const bool _static = false) {
        collider.sphereCollider = Sphere(_center, _radius);
        isTrigger = _trigger;
        isStatic = _static;
        type = colType::SPHERE;
    }

    colType type;
    Collider collider;

    bool isTrigger = false;
    bool isStatic = false;
    
    bool collidingBelow = false;
};

#endif //VAPEENGINE_COLLIDERCOMPONENT_H
