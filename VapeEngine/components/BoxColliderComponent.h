//
// Created by l3gume on 23/02/18.
//

#include <ecs/ecs.h>

#ifndef VAPEENGINE_BOXCOLLIDERCOMPONENT_H
#define VAPEENGINE_BOXCOLLIDERCOMPONENT_H

using namespace ECS;

struct BoxColliderComponent : Component {
    /*
     * Constructor, give it the bottom left near corner (-z = near) and dimensions.
     */
    BoxColliderComponent(glm::vec3 _bottomLeftNear, const float _x, const float _y, const float _z)  {
        assert(_bottomLeftNear.x < _x && _bottomLeftNear.y < _y && _bottomLeftNear.z < _z); // validate points
        bottomLeftNear = _bottomLeftNear;
        topRightFar = glm::vec3(bottomLeftNear.x + _x, bottomLeftNear.y + _y, bottomLeftNear.z + _z);
    }
    /*
     * Other constructor, using two points.
     */
    BoxColliderComponent(glm::vec3 _bottomLeftNear, glm::vec3 _topRightFar) {
        assert(_bottomLeftNear.x < _topRightFar.x && _bottomLeftNear.y < _topRightFar.y && _bottomLeftNear.z < _topRightFar.z); // validate points
        bottomLeftNear = _bottomLeftNear;
        topRightFar = _topRightFar;
    }

    // Two opposed corners of the box.
    glm::vec3 bottomLeftNear;
    glm::vec3 topRightFar;

    bool isTrigger = false;
};

#endif //VAPEENGINE_BOXCOLLIDERCOMPONENT_H
