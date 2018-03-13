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
                            case CollisionType::BOX_TO_BOX:
                                resolveAABBCollision(col);
                                break;
                            case CollisionType::SPHERE_TO_SPHERE:
                                resolveSphereCollision(col);
                                break;
                            case CollisionType::BOX_TO_SPHERE:
                                resolveAABBSphereCollision(col);
                                break;
                        }
                    }
                }
            }
        }
    }
}

bool CollisionSystem::testCollision(Entity *e1, Entity *e2, Collision &col) {
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

        bool collision = (x < 0.f && y < 0.f && z < 0.f);
        if (collision) {
            col.type = CollisionType::BOX_TO_BOX;
            col.e1 = e1;
            col.e2 = e2;
            col.e1_isTrigger = c1.isTrigger;
            col.e2_isTrigger = c2.isTrigger;
            col.e1_isStatic = c1.isStatic;
            col.e2_isStatic = c2.isStatic;
            col.e1_Sphere = c1.collider.sphereCollider;
            col.e1_AABB = c1.collider.boxCollider;
            col.e2_Sphere = c2.collider.sphereCollider;
            col.e2_AABB = c2.collider.boxCollider;
            col.intersectX = x;
            col.intersectY = y;
            col.intersectZ = z;
            col.dx = dx;
            col.dy = dy;
            col.dz = dz;
        }
        return collision;
    } else if ((c1.type == BOX && c2.type == SPHERE) || (c2.type == BOX && c1.type == SPHERE)) {
        glm::vec3 closest =
                c1.type == SPHERE ? closestPointOnAABB(c1.collider.sphereCollider.c, c2.collider.boxCollider)
                                  : closestPointOnAABB(c2.collider.sphereCollider.c, c1.collider.boxCollider);
        float dist =
                c1.type == SPHERE ? squaredDistPointAABB(c1.collider.sphereCollider.c, c2.collider.boxCollider)
                                  : squaredDistPointAABB(c2.collider.sphereCollider.c, c1.collider.boxCollider);
        float rad = c1.type == SPHERE ? c1.collider.sphereCollider.r : c2.collider.sphereCollider.r;
        glm::vec3 sphere = c1.type == SPHERE ? c1.collider.sphereCollider.c : c2.collider.sphereCollider.c;
        bool collision = (sqrMagnitude(closest - sphere) <= rad * rad);
        if (collision) {

            glm::vec3 normal = sphere - closest;

            col.type = BOX_TO_SPHERE;
            col.e1 = e1;
            col.e2 = e2;
            col.e1_type = c1.type;
            col.e2_type = c2.type;
            col.e1_Sphere = c1.collider.sphereCollider; // Better be careful here, depending on the type, some data may
            col.e1_AABB = c1.collider.boxCollider;      // be "corrupted" since its an union.
            col.e2_Sphere = c2.collider.sphereCollider;
            col.e2_AABB = c2.collider.boxCollider;
            col.e1_isTrigger = c1.isTrigger;
            col.e2_isTrigger = c2.isTrigger;
            col.e1_isStatic = c1.isStatic;
            col.e2_isStatic = c2.isStatic;
            col.sqDist = dist;
            col.normal = normal != glm::vec3(0.f) ? glm::normalize(normal) : defaultUpVector();
        }
        return collision;
    } else if (c1.type == colType::SPHERE && c2.type == colType::SPHERE) {
        glm::vec3 normal = c1.collider.sphereCollider.c - c2.collider.sphereCollider.c; 
        float distSqr = dot(normal, normal);
        bool collision = (glm::sqrt(distSqr) <= c1.collider.sphereCollider.r + c2.collider.sphereCollider.r);
        if (collision) {
            col.type = CollisionType::SPHERE_TO_SPHERE;
            col.e1 = e1;
            col.e2 = e2;
            col.e1_isTrigger = c1.isTrigger;
            col.e2_isTrigger = c2.isTrigger;
            col.e1_isStatic = c1.isStatic;
            col.e2_isStatic = c2.isStatic;
            col.e1_Sphere = c1.collider.sphereCollider; col.e1_AABB = c1.collider.boxCollider;
            col.e2_Sphere = c2.collider.sphereCollider;
            col.e2_AABB = c2.collider.boxCollider;
            col.normal = normal != glm::vec3(0.f) ? glm::normalize(normal) : defaultUpVector();
            col.sqDist = distSqr;
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
    if (col.e1_isTrigger || col.e2_isTrigger) {
        // things (handler functions to call)
    } else {
        if (!col.e1_isStatic) {
            auto &transform = col.e1->getComponent<TransformComponent>();
            if (!col.e1->getParent()) {
                transform.position += col.normal * ((col.e1_Sphere.r + col.e2_Sphere.r) - glm::sqrt(col.sqDist));
            }
        }
    }
}

void CollisionSystem::resolveAABBSphereCollision(Collision &col) {
    if (col.e1_isTrigger || col.e2_isTrigger) {
        // do the ting
    } else {
        if (!col.e1_isStatic) {
            auto &transform = col.e1->getComponent<TransformComponent>();
            if (!col.e1->getParent()) {
                if (col.e1_type == SPHERE)
                    transform.position += col.normal * ((col.e1_type == SPHERE ? col.e1_Sphere.r : col.e2_Sphere.r) - glm::sqrt(col.sqDist));
                else if (col.e1_type == BOX)
                    transform.position -= col.normal * ((col.e1_type == SPHERE ? col.e1_Sphere.r : col.e2_Sphere.r) - glm::sqrt(col.sqDist));
            }
        }
    }
}

glm::vec3 CollisionSystem::closestPointOnAABB(const glm::vec3 &_p, const AABB &_aabb) {
    // little lambda action
    auto check = [&](const float _pn, const float _bmin, const float _bmax) -> float {
        float v = _pn;
        v = glm::max(v, _bmin);
        v = glm::min(v, _bmax);
        return v;
    };

    glm::vec3 sq{
            check(_p.x, _aabb.c.x - _aabb.r.x, _aabb.c.x + _aabb.r.x),
            check(_p.y, _aabb.c.y - _aabb.r.y, _aabb.c.y + _aabb.r.y),
            check(_p.z, _aabb.c.z - _aabb.r.z, _aabb.c.z + _aabb.r.z)
    };

    return sq;
}

float CollisionSystem::squaredDistPointAABB(const glm::vec3 &_p, const AABB &_aabb) {
    auto check = [&](
            const float pn,
            const float bmin,
            const float bmax) -> float {
        float out = 0;
        float v = pn;

        if (v < bmin) {
            float val = (bmin - v);
            out += val * val;
        }

        if (v > bmax) {
            float val = (v - bmax);
            out += val * val;
        }

        return out;
    };

    // Squared distance
    float sq = 0.0;

    sq += check(_p.x, _aabb.c.x - _aabb.r.x, _aabb.c.x + _aabb.r.x);
    sq += check(_p.y, _aabb.c.y - _aabb.r.y, _aabb.c.y + _aabb.r.y);
    sq += check(_p.z, _aabb.c.z - _aabb.r.z, _aabb.c.z + _aabb.r.z);

    return sq;
}
