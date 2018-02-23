//
// Created by l3gume on 23/02/18.
//

#ifndef VAPEENGINE_COLLISIONHANDLERCOMPONENT_H
#define VAPEENGINE_COLLISIONHANDLERCOMPONENT_H

#include <ecs/ecs.h>

using namespace ECS;

/*
 * data object to pass the info of a collision
 */
struct Collision {

};

/*
 * Holds function pointers that will be set by scripts to handle the entity's collisions.
 */
struct CollisionHandlerComponent : Component {
    CollisionHandlerComponent() = default;

    void (*onCollision)(Collision) = nullptr;
    void (*onTriggerEnter)(Collision) = nullptr;
    void (*onTriggerStay)(Collision) = nullptr;
};

#endif //VAPEENGINE_COLLISIONHANDLERCOMPONENT_H
