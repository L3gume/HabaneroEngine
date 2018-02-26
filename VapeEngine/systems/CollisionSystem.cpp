//
// Created by l3gume on 26/02/18.
//

#include "CollisionSystem.h"

void CollisionSystem::update(float _deltaTime) {
    auto &entities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
            getComponentTypeID<BoxColliderComponent>());

    if (!entities.empty()) {
        for (auto &e1 : entities) {
            for (auto &e2 : entities) {
                if (e1 != e2) {
                    if (Collision col{}; testAABBCollision(e1, e2, col)) {
                        if (col.e1_isTrigger || col.e2_isTrigger) {
                            // no position adjustment}
                        } else {
                            // position adjustment
                            if (!col.e1_isStatic) {
                                auto &transform = e1->getComponent<TransformComponent>();
                                if (!e1->getParent()) {
                                    transform.position -= col.e1_AABB.velocity * 2.f * _deltaTime;
                                    transform.abs_position -= col.e1_AABB.velocity * 2.f * _deltaTime;
                                }
                            }
//                            if (!col.e2_isStatic) {
//                                auto &transform = e2->getComponent<TransformComponent>();
//                                if (!e2->getParent())
//                                    transform.position -= col.e2_AABB.velocity * _deltaTime;
//                            }
                        }
                    }
                }
            }
        }
    }
}

bool CollisionSystem::testAABBCollision(Entity *e1, Entity *e2, Collision &col) {
    auto &c1 = e1->getComponent<BoxColliderComponent>();
    auto &c2 = e2->getComponent<BoxColliderComponent>();
    if (!(c1.m_bEnabled && c2.m_bEnabled)) return false;
    auto &a = c1.collider;
    auto &b = c2.collider;
    bool x = std::fabs(a.c[0] - b.c[0]) <= (a.r[0] + b.r[0]);
    bool y = std::fabs(a.c[1] - b.c[1]) <= (a.r[1] + b.r[1]);
    bool z = std::fabs(a.c[2] - b.c[2]) <= (a.r[2] + b.r[2]);

    bool collision = x && y && z;
    if (collision) {
        col.e1 = e1;
        col.e2 = e2;
        col.e1_isTrigger = c1.isTrigger;
        col.e2_isTrigger = c2.isTrigger;
        col.e1_AABB = a;
        col.e2_AABB = b;
    }
    return collision;
}
