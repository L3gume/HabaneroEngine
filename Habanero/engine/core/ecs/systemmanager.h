#pragma once
#ifndef ECS_SYSTEMMANAGER_H
#define ECS_SYSTEMMANAGER_H

#include "system.h"

namespace ecs
{
/*
 * SystemManager class, handles the various systems
 */
class SystemManager {
private:
	std::vector<System*> m_systems;
public:
	SystemManager() = default;
	~SystemManager() = default;

	template<typename T, typename... TArgs>
	T &addSystem(TArgs&&... _args) {
		ComponentID _typeID = getComponentTypeID<T>();
		const auto& found = std::find_if(std::begin(m_systems), std::end(m_systems),
							   [_typeID](System* _sys) { return _sys->typeID == _typeID; });
		if (found != std::end(m_systems)) {
			// System already exists.
			assert(false);
		}

		auto system = new T(std::forward<TArgs>(_args)...);
		system->systemManager = this;
		system->typeID = getComponentTypeID<T>();
		m_systems.emplace_back(system);

		// Sort the systems by priority
		std::sort(std::begin(m_systems), std::end(m_systems), [](System* _s1, System* _s2){
			return _s1->m_priority > _s2->m_priority;
		});

		return *system;
	};

	template<typename T>
	T* getSystem() const
	{
		ComponentID _typeID = getComponentTypeID<T>();
		auto found = std::find_if(std::begin(m_systems), std::end(m_systems),
								   [_typeID](System* _sys) { return _sys->typeID == _typeID; });
		return found != this->m_systems.end() ? static_cast<T*>(*found) : nullptr;
	}

	template<typename T>
	void setSystemPriority(uint8_t _priority) {
		ComponentID _typeID = getComponentTypeID<T>();
		const auto& found = std::find_if(std::begin(m_systems), std::end(m_systems),
									   [_typeID](System* _sys) { return _sys->typeID == _typeID; });
		if (found != std::end(m_systems)) {
			// System already exists.
			(*found)->m_priority = _priority;
		} else {
			// system isn't in there.
			assert(false);
			return;
		}

		// Sort the systems by priority
		std::sort(std::begin(m_systems), std::end(m_systems), [](System* _s1, System* _s2){
			return _s1->m_priority > _s2->m_priority;
		});
	}

	void preUpdate(const float _deltaTime) {
		for (auto& sys : m_systems) {
			sys->preUpdate(_deltaTime);
		}
	}

	void update(const float _deltaTime) {
		for (auto& sys : m_systems) {
			sys->update(_deltaTime);
		}
	}

	void postUpdate(const float _deltaTime) {
		for (auto& sys : m_systems) {
			sys->postUpdate(_deltaTime);
		}
	}
};
}

#endif
