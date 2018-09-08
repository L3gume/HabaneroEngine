#pragma once
#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include "ecs.h"

namespace ecs
{
	
class Entity;
	
/*
 * Component Implementation
 *
 * A component is a logic-less data object. it only contains data that will be handled by a system.
 */
struct Component {
	Entity *m_entity{ nullptr };

	// ... stuff ...
	bool m_bEnabled;

	virtual ~Component() {}
};

} // namespace ecs

#endif