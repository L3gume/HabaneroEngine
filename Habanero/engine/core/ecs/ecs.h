//
// Created by notjustin on 2/8/18.
//

/*
 * TODO: implement allocators
 */
#pragma once
#ifndef ECS_ECS_H
#define ECS_ECS_H

#include <vector>
#include <memory>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <d3d11.h>


#include "boost/algorithm/string/predicate.hpp"
#include "boost/lexical_cast.hpp"
#include "engine/core/logging/LogManager.h"
#include "engine/core/logging/LogMessage.h"
#include "libraries/DirectXTK/include/SimpleMath.h"
#include "../util.h"

using HabaneroLog::LogManager;
using HabaneroLog::LogMessage;
using HabaneroLog::LogTag;
using HabaneroLog::LogType;
using HabaneroLog::LogSeverity;

namespace ecs
{

/*
 * Constexpr and typedef
 */
constexpr std::size_t MAX_COMPS{32};
constexpr std::size_t MAX_GROUPS{32};

using ComponentID = std::size_t;
using Group = std::size_t;
using GroupBitset = std::bitset<MAX_GROUPS>;

/*
 * Stuff
 */
inline ComponentID getUniqueComponentID() noexcept {
	static ComponentID lastID{0u};
	return lastID++;
}

// Template Magic, have fun trying to figure it out!
template<typename T>
ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID{getUniqueComponentID()};
	return typeID;
}
}
#endif //ECS_ECS_H
