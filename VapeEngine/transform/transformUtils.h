#ifndef TRANSFORM_UTIL_H
#define TRANSFORM_UTIL_H

#include <components/TransformComponent>

namespace Transform {
    static void translate(const ECS::TransformComponent* _transform, const glm::vec3 _delta);
    static void rotateEuler(const ECS::TransformComponent* _transform, const glm::vec3 _delta);
    static void rotateAroundAxis(const ECS::TransformComponent* _transform, const glm::vec3 _axis, const float _angle);
    
    static void moveTo(const ECS::TransformComponent* _transform, const glm::vec3 _pos, const float _deltaTime);
    static void moveAndRotateTo(const ECS::TransformComponent* _transform, const glm::vec3 _pos, const float _deltaTime);
    static void rotateTo(const ECS::TransformComponent* _transform, const glm::vec3 _pos);
    static void rotateTo(const ECS::TransformComponent* _transform, const glm::vec3 _pos, const float _maxSpeed);
    
    // TODO
    static void LERP();
    static void SLERP();
}

#endif
