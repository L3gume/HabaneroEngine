//
// Created by l3gume on 19/02/18.
//
#include "TransformSystem.h"

#include "engine/core/Engine.h"
#include "engine/core/components/TransformComponent.h"

void TransformSystem::update(float _deltaTime) {
	// TODO: We might want to rethink how we're doing this. There are two ways we can remove the need
	// to make this copy: 1) Don't sort the vector, allowing us to just get a const ref to the 
	// entity list or 2) Expose a way to sort the entity list directly in the EntityManager. The second
	// option is probably a really bad idea. The first idea is the best imo, because there really is no
	// need to sort the the list to have child transforms coming first (if I'm understanding this correctly)
	std::vector<Entity*> entities;
	if (Core::Engine::getInstance().getEntityManager().hasEntitiesInGroup(
		getComponentTypeID<TransformComponent>())) {
		entities = *(Core::Engine::getInstance().getEntityManager().getMutableEntitiesByGroup(
			getComponentTypeID< TransformComponent>()));
	}

    std::sort(std::begin(entities), std::end(entities), [](const Entity* A, const Entity* B) {
        return A->getParent() != nullptr && B->getParent() == nullptr;
    });
    for (auto& e : entities) {
        if (!e->getParent()) {
            continue;
        } else {
            assert(e->getParent()->hasComponent<TransformComponent>());
            auto& parent_transform = e->getParent()->getComponent<TransformComponent>();
            auto& transform = e->getComponent<TransformComponent>();

			// TODO porting this to use DirectXMath was not trivial unfortunetely, we should figure out how to 
			// port it once we actually need to use this system (this is blocking getting meshes rendering)
			/*
            transform.abs_position = parent_transform.position + glm::quat(parent_transform.rotation) * transform.position;
            transform.abs_rotation = glm::eulerAngles(glm::quat(parent_transform.rotation) * glm::quat(transform.rotation));
            transform.abs_scale = transform.scale * parent_transform.scale;
			*/
        }
    }
}
