#pragma once
#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "ecs.h"

namespace ecs
{
/*
 * System class, templated to only handle one type of component, only the manager can construct one
 */
class System {
	friend class SystemManager;

public:
	virtual ~System() {}

	void enable() noexcept { m_enabled = true; }
	void disable() noexcept { m_enabled = false; }
protected:
	System() : /*typeID(getComponentTypeID<T>()),*/ m_enabled(true) {} // = default?

	ComponentID typeID;
	bool m_enabled;
#if EDITOR
	bool m_enabledInEditorMode;
#endif
	uint8_t m_priority;
private:
	SystemManager *systemManager; // hold ref to sys manager

	virtual void preUpdate(float _deltaTime) {}
	virtual void update(float _deltaTime) {}
	virtual void postUpdate(float _deltaTime) {}
};
}
#endif
