//
// Created by l3gume on 19/02/18.
//

#include <core/Engine.h>
#include <components/TransformComponent.h>
#include <components/CameraComponent.h>
#include <components/BoxColliderComponent.h>
#include "TransformSystem.h"

void TransformSystem::update(float _deltaTime) {
    std::vector<Entity *> entities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
            getComponentTypeID<TransformComponent>());
    std::sort(std::begin(entities), std::end(entities), [](const Entity *A, const Entity *B) {
        return A->getParent() != nullptr && B->getParent() == nullptr;
    });
    for (auto &e : entities) {
        auto &transform = e->getComponent<TransformComponent>();
        if (!e->getParent()) {
            transform.abs_position = transform.position;
            transform.abs_rotation = transform.rotation;
            transform.abs_scale = transform.scale;
        } else {
            assert(e->getParent()->hasComponent<TransformComponent>());
            auto &parent_transform = e->getParent()->getComponent<TransformComponent>();

            transform.abs_position =
                    parent_transform.position + glm::quat(parent_transform.rotation) * transform.position;
            transform.abs_rotation = glm::eulerAngles(
                    glm::quat(parent_transform.rotation) * glm::quat(transform.rotation));
            transform.abs_scale = transform.scale * parent_transform.scale;
        }
        if (e->hasComponent<BoxColliderComponent>()) {
            auto &box = e->getComponent<BoxColliderComponent>();
            if (!box.isStatic) {
//                box.collider.velocity.x = (transform.abs_position.x - box.collider.c.x) / _deltaTime;
//                box.collider.velocity.y = (transform.abs_position.y - box.collider.c.y) / _deltaTime;
//                box.collider.velocity.z = (transform.abs_position.z - box.collider.c.z) / _deltaTime;

                float dx = transform.abs_position.x - box.collider.c.x;
                float dy = transform.abs_position.y - box.collider.c.y;
                float dz = transform.abs_position.z - box.collider.c.z;

                float d = glm::sqrt(dx * dx + dy * dy + dz * dz);
                float s = d / _deltaTime;

                box.collider.velocity = glm::vec3((dx/d)*s,(dy/d)*s,(dz/d)*s);

//                box.collider.velocity = (transform.abs_position - box.collider.c) / _deltaTime;

                box.collider.c = transform.abs_position;
            }
        }
    }
}
