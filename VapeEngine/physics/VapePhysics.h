#ifndef VAPEENGINE_VAPEPHYSICS_H
#define VAPEENGINE_VAPEPHYSICS_H

namespace physics {
    void applyImpulse(RigidBodyComponent _target, glm::vec3 _direction, float _magnitude);
    void applyForce(RigidBodyComponent _target, glm::vec3 _direction, float _magnitude, float _deltaTime);
}

#endif
