//
// Created by l3gume on 2018-03-12
//
#ifndef VAPEENGINE_RIGIDBODYCOMPONENT_H
#define VAPEENGINE_RIGIDBODYCOMPONENT_H

#include <ecs/ecs.h>

using namespace ECS;

struct RigidBodyComponent : Component {
    /*
     * Default Constructor
     */
    RigidBodyComponent() {
        lockPos_x = false;
        lockPos_y = false;
        lockPos_z = false;
        lockRot_x = false;
        lockRot_y = false;
        lockRot_z = false;
    }
    
    /*
     * constructor with all arguments (mostly for serialization)
     */
    RigidBodyComponent(float _gravScl, float _mass, float _friction, 
                        bool _lckPosx, bool _lckPosy, bool _lckPosz, 
                        bool _lckRotx, bool _lckRoty, bool _lckRotz) {
        gravityScale = _gravScl;
        mass = _mass;
        friction = _friction;
        
        lockPos_x = _lckPosx;
        lockPos_y = _lckPosy;
        lockPos_z = _lckPosz;
        lockRot_x = _lckRotx;
        lockRot_y = _lckRoty;
        lockRot_z = _lckRotz;
    }
    
    float gravityScale  = 1.f;
    float mass          = 1.f;
    float friction      = 1.f;
    
    glm::vec3 velocity;

    bool lockPos_x      : 1;
    bool lockPos_y      : 1;
    bool lockPos_z      : 1;
    bool lockRot_x      : 1;
    bool lockRot_y      : 1;
    bool lockRot_z      : 1;
    bool isKinematic    : 1;
}

#endif
