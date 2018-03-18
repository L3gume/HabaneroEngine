#include <systems/PhysicsSystem.h>

void PhysicsSystem::preUpdate(float _deltaTime) {
    // get the entities, made a member variable so we don't have to fetch them again
    //m_entities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(getComponentTypeID<RigidBodyComponent>());
    
    // Apply gravity force
    //for (auto &e : m_entities) {
    //    auto &rb = e->getComponent<RigidBodyComponent>();
    //    if (!rb.isKinematic && !rb.lockPos_y) {
    //        physics::applyForce(rb, -defaultUpVector(), 9.8f, _deltaTime);
    //    }
    //}
}

void PhysicsSystem::update(float _deltaTime) {
    // get the entities, made a member variable so we don't have to fetch them again
    m_entities = Core::Engine::getInstance().getEntityManager().getEntitiesByGroup(getComponentTypeID<RigidBodyComponent>());
    
    for (auto &e : m_entities) {
        auto &rb = e->getComponent<RigidBodyComponent>();
        if (!rb.isKinematic && !rb.lockPos_y) {
            //physics::applyForce(rb, -defaultUpVector(), rb.mass * 9.8f, _deltaTime);
            rb.accel += rb.gravityScale * 9.8f * -defaultUpVector() * glm::sqrt(_deltaTime);
        }
        
        assert(e->hasComponent<TransformComponent>());
                
        auto &transform = e->getComponent<TransformComponent>();
        
        // TODO: add position lock checks
        
        transform.position += rb.velocity * _deltaTime; // adjust position, this will be done before the transform system
        
        // Apply the "friction" to slow the body down, will be added next frame.
        physics::applyForce(rb, -rb.velocity, rb.friction, _deltaTime); 
    }
}
