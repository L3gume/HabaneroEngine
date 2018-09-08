#pragma once
#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include "ecs.h"
#include "component.h"

namespace ecs
{
	
class EntityManager;
	
using ComponentBitset = std::bitset<MAX_COMPS>;
using ComponentArray = std::array<Component *, MAX_COMPS>;
	
class Entity {
	friend class EntityManager;
	friend class EntityConstructor;
private:
	EntityManager* m_manager;
	/*
	 * Unique_ptrs make it so we don't leak any memory
	 */
	std::vector<std::unique_ptr<Component>> m_components;
	ComponentBitset m_componentBitset;
	ComponentArray m_componentArray;
	GroupBitset m_groupBitset;

	std::vector<Entity*> m_children;
	Entity* m_parent;

	std::string m_sName;
	uint64_t m_iId;

	bool m_bDestroyed = false; // entity will be removed from manager when this is true. Components are unique_ptr
							   // so no need to worry about them
public:
	std::string getName() const { return m_sName; }
	uint64_t getId() const { return m_iId; }
	const Entity* getParent() const { return m_parent; }
	const std::vector<Entity*>& getChildren() const { return m_children; };
	void destroy() { m_bDestroyed = true; }
	
	/*
	 * Check if the entity already has an instance of component T
	 */
	template<typename T>
	bool hasComponent() const {
		return m_componentBitset[getComponentTypeID<T>()];
	}

	/*
	 * Check if entity belongs to a group
	 */
	bool hasGroup(Group _group) const noexcept {
		return m_groupBitset[_group];
	}

	/*
	 * Add entity to group
	 */
	void addGroup(Group _group) noexcept;

	/*
	 * Remove entity from group, the manager will automatically get rid of it
	 */
	void deleteFromGroup(Group _group) noexcept {
		m_groupBitset[_group] = false;
	}

	/*
	 * Add a component to the entity
	 */
	template<typename T, typename... TArgs>
	T &addComponent(TArgs &&... _args) {
		assert(!hasComponent<T>()); // Make sure the entity doesn't already have this type of component.

		T *c(new T(std::forward<TArgs>(_args)...));
		c->m_entity = this;
		std::unique_ptr<Component> uPtr(std::move(c));
		m_components.emplace_back(std::move(uPtr));

		ComponentID id = getComponentTypeID<T>();
		m_componentArray[id] = c;
		m_componentBitset[id] = true;

		this->addGroup(id);
		c->m_bEnabled = true;

		return *c;
	}

	/*
	 * Get the entity's component T, if it has one.
	 */
	template<typename T>
	T &getComponent() const {
		assert(hasComponent<T>()); // will throw an error
		auto ptr(m_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T *>(ptr);
	}
};
	
}

#endif