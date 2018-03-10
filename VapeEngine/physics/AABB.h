//
// Created by l3gume on 26/02/18.
//

#ifndef VAPEENGINE_AABB_H
#define VAPEENGINE_AABB_H

#include <glm/vec3.hpp>

struct AABB {
    AABB() : c(), r() {}
    AABB(const glm::vec3 &_center, const glm::vec3 &_halfWidths)
            : c(_center), r(_halfWidths) {}

    glm::vec3 c; // Center point
    glm::vec3 r; // halfwidths

    glm::vec3 velocity;
};

#endif //VAPEENGINE_AABB_H
