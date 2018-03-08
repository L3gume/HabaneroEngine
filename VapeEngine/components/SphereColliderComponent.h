//
// Created by l3gume on 05/03/18
//
#ifndef VAPEENGINE_SPHERECOLLIDERCOMPONENT_H
#define VAPEENGINE_SPHERECOLLIDERCOMPONENT_H

#include <ecs/ecs.h>
#include <physics/Sphere.h>

using namespace ECS;

struct SphereColliderComponent : Component {
    SphereColliderComponent(const glm::vec3& _center, const float _radius) {
        collider = Sphere(_center, _radius);            
    }
    
    SphereColliderComponent(const glm::vec3& _center, const float _radius, bool _trig, bool _stat) {
        collider = Sphere(_center, _radius);
        isTrigger = _trig;
        isStatic = _stat;
    }
    
    Sphere collider;
    bool isTrigger = false;
    bool isStatic = false;
};

#endif
