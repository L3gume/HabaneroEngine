//
// Created by l3gume on 26/02/18.
//

#include "CollisionSystem.h"
#include <components/CollisionHandlerComponent.h>
#include <components/ColliderComponent.h>

void CollisionSystem::update(float _deltaTime) {
//    auto &entities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
//            getComponentTypeID<BoxColliderComponent>());
    auto &entities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(
            getComponentTypeID<ColliderComponent>());

    if (!entities.empty()) {
        for (auto &e1 : entities) {
            for (auto &e2 : entities) {
                if (e1 != e2) {
                    if (Collision col{}; testCollision(e1, e2, col)) {
                        switch (col.type) {
                            case CollisionType::BOX_TO_BOX: resolveAABBCollision(col); break;
                            case CollisionType::SPHERE_TO_SPHERE:
                                break;
                            case CollisionType::BOX_TO_SPHERE:
                                break;
                        }
//                        resolveAABBCollision(col);
                    }
                }
            }
        }
    }
}

bool CollisionSystem::testCollision(Entity *e1, Entity *e2, Collision &col) {
//    auto &c1 = e1->getComponent<BoxColliderComponent>();
//    auto &c2 = e2->getComponent<BoxColliderComponent>();
    auto &c1 = e1->getComponent<ColliderComponent>();
    auto &c2 = e2->getComponent<ColliderComponent>();
    if (!(c1.m_bEnabled && c2.m_bEnabled)) return false;
    if (c1.type == colType::BOX && c2.type == colType::BOX) {
        auto &a = c1.collider.boxCollider;
        auto &b = c2.collider.boxCollider;
        float dx = a.c[0] - b.c[0];
        float dy = a.c[1] - b.c[1];
        float dz = a.c[2] - b.c[2];
        float x = std::fabs(dx) - (a.r[0] + b.r[0]);
        float y = std::fabs(dy) - (a.r[1] + b.r[1]);
        float z = std::fabs(dz) - (a.r[2] + b.r[2]);

        bool collision = x < 0.f && y < 0.f && z < 0.f;
        if (collision) {
            col.type = CollisionType::BOX_TO_BOX;
            col.e1 = e1;
            col.e2 = e2;
            col.e1_isTrigger = c1.isTrigger;
            col.e2_isTrigger = c2.isTrigger;
            col.e1_isStatic = c1.isStatic;
            col.e2_isStatic = c2.isStatic;
            col.e1_AABB = a;
            col.e2_AABB = b;
            col.intersectX = x;
            col.intersectY = y;
            col.intersectZ = z;
            col.dx = dx;
            col.dy = dy;
            col.dz = dz;
        }
        return collision;
    }
}

void CollisionSystem::resolveAABBCollision(Collision &col) {
    if (col.e1_isTrigger || col.e2_isTrigger) {
        // no position adjustment
    } else {
        // position adjustment
        if (!col.e1_isStatic) {
            auto &transform = col.e1->getComponent<TransformComponent>();
            if (!col.e1->getParent()) {
                if (col.intersectX > col.intersectY && col.intersectX > col.intersectZ) {
                    if (col.dx < 0.f) {
                        transform.position =
                                transform.position + glm::vec3(col.intersectX, 0.f, 0.f);
                        transform.abs_position =
                                transform.abs_position + glm::vec3(col.intersectX, 0.f, 0.f);
                    } else {
                        transform.position =
                                transform.position + glm::vec3(-col.intersectX, 0.f, 0.f);
                        transform.abs_position =
                                transform.abs_position + glm::vec3(-col.intersectX, 0.f, 0.f);
                    }
                } else if (col.intersectY > col.intersectX && col.intersectY > col.intersectZ) {
                    if (col.dy < 0.f) {
                        transform.position =
                                transform.position + glm::vec3(0.f, col.intersectY, 0.f);
                        transform.abs_position =
                                transform.abs_position + glm::vec3(0.f, col.intersectY, 0.f);
                    } else {
                        transform.position =
                                transform.position + glm::vec3(0.f, -col.intersectY, 0.f);
                        transform.abs_position =
                                transform.abs_position + glm::vec3(0.f, -col.intersectY, 0.f);
                    }
                } else {
                    if (col.dz < 0.f) {
                        transform.position =
                                transform.position + glm::vec3(0.f, 0.f, col.intersectZ);
                        transform.abs_position =
                                transform.abs_position + glm::vec3(0.f, 0.f, col.intersectZ);
                    } else {
                        transform.position =
                                transform.position + glm::vec3(0.f, 0.f, -col.intersectZ);
                        transform.abs_position =
                                transform.abs_position + glm::vec3(0.f, 0.f, -col.intersectZ);
                    }
                }
            }
        }
    }
}

void CollisionSystem::resolveSphereCollision(Collision &col) {

}

void CollisionSystem::resolveAABBSphereCollision(Collision &col) {

}

