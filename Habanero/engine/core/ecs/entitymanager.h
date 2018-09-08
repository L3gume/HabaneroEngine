#pragma once
#ifndef ECS_ENTITYMANAGER_H
#define ECS_ENTITYMANAGER_H

#include "entity.h"

namespace ecs
{
class EntityManager {
private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::array<std::vector<Entity *>, MAX_GROUPS> m_groupedEntities;

	// This is used in the case where an invalid group is passed to
	// getEntitiesByGroup. Since that method return a reference, it's best
	// to return a reference to this empty vector (which will remain in scope)
	// than returning a reference to a local variable.
	// TODO: once there's a way to properly terminate the program, replace the use
	// of this vector with a program termination
	const std::vector<Entity*> m_emptyVector;
public:
	/* Add a function to remove entities that have to be removed */
	void refresh() {
		/*
		 * Remove entites that don't belong to groups anymore and those that have been destroyed.
		 */
		for (auto i{0u}; i < MAX_GROUPS; i++) {
			auto &v{m_groupedEntities[i]};
			v.erase(std::remove_if(std::begin(v), std::end(v),
		
								   [i](Entity *_ent) {
									   return !_ent->hasGroup(i) || _ent->m_bDestroyed;
								   }), std::end(v));
		}
	}

	/*
	 * Add an entity to the manager.
	 */
	Entity &addEntity(std::string _name) {
		Entity *e{new Entity{}};

		e->m_manager = this;
		e->m_sName = std::move(_name); // since we're passing by copy and only copying once.
		e->m_iId = generateUniqueID(); // may be useful

		std::shared_ptr<Entity> sPtr(e);
		m_entities.emplace_back(std::move(sPtr));
		return *e;
	}

	/*
	 * Add an Entity to a group
	 */
	void addToGroup(Entity *_ent, Group _group) {
		m_groupedEntities[_group].emplace_back(_ent);
	}

	/*
	 * Helper method to check if any entities of a given group exist
	*/
	bool hasEntitiesInGroup(Group _group) {
		return (_group < MAX_GROUPS) && !m_groupedEntities[_group].empty();
	}

	/*
	 * Get a group of entities, this will be handy for separating entites by the components they have.
	 */
	const std::vector<Entity *> &getEntitiesByGroup(Group _group) {
		if (_group >= MAX_GROUPS) {
			LogManager::getInstance().printMessage(
				LogMessage(
					LogTag::ECS, LogType::BUG, LogSeverity::CRITICAL,
					"Group given to getEntitiesByGroup is larger than max group"));
			
			return m_emptyVector;
		}

		return m_groupedEntities[_group];
	}

	std::vector<Entity *> *getMutableEntitiesByGroup(Group _group) {
		if (_group >= MAX_GROUPS) {
			LogManager::getInstance().printMessage(
				LogMessage(
					LogTag::ECS, LogType::BUG, LogSeverity::CRITICAL,
					"Group given to getMutableEntitiesByGroup is larger than max group"));
			return nullptr;
		}
		return &m_groupedEntities[_group];
	}

	std::vector<std::shared_ptr<Entity>> &getEntities() { return m_entities; }

	static void loadEntity(const std::string& _path);
};
} // namespace ecs

#endif