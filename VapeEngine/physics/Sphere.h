//
// Created by l3gume on 05/03/18
//
#ifndef VAPEENGINE_SPHERE_H
#define VAPEENGINE_SPHERE_H

#include <glm/vec3.hpp>

struct Sphere {
    Sphere() : c(), r(0.f) {}
    Sphere(const glm::vec3& _center, float _radius) : c(_center), r(_radius) {}
    
    glm::vec3 c;
    float r;
};

#endif
