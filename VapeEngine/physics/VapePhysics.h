#ifndef VAPEENGINE_VAPEPHYSICS_H
#define VAPEENGINE_VAPEPHYSICS_H

#include <components/RigidBodyComponent.h>
#include <glm/glm.hpp>

namespace physics {
    void applyImpulse(RigidBodyComponent& _target, glm::vec3 _direction, const float _magnitude);
    void applyForce(RigidBodyComponent& _target, glm::vec3 _direction, const float _magnitude, const float _deltaTime);
}

#endif
