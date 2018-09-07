//
// Created by l3gume on 19/02/18.
//
#pragma once
#ifndef HABANERO_CONSTRUCTORFUNCTIONS_H
#define HABANERO_CONSTRUCTORFUNCTIONS_H

#include <iostream>

#include "glm/glm.hpp"
#include "engine/core/ecs/entity.h"
#include "engine/core/components/TransformComponent.h"
#include "engine/core/components/RenderableComponent.h"
#include "engine/core/components/CameraComponent.h"
#include "engine/core/components/ScriptComponent.h"

using namespace ecs;

/*
 * The point of this file is to add components here so they can be saved/loaded
 */

void constructTransformComponent(Entity& _ent, std::vector<std::string>& _args);
void constructRenderableComponent(Entity& _ent, std::vector<std::string>& _args);
void constructCameraComponent(Entity& _ent, std::vector<std::string>& _args);
void constructScriptComponent(Entity& _ent, std::vector<std::string>& _args);

void saveTransformComponent(Entity& _ent, std::ostringstream& _oss);
void saveRenderableComponent(Entity& _ent, std::ostringstream& _oss);
void saveCameraComponent(Entity& _ent, std::ostringstream& _oss);
void saveScriptComponent(Entity& _ent, std::ostringstream& _oss);

static std::string xmlFieldStart(const char* str) {
	std::stringstream ss;
	ss << "<" << str << ">";
	return ss.str();
}

static std::string xmlFieldEnd(const char* str) {
	std::stringstream ss;
	ss << "</" << str << ">";
	return ss.str();
}

template<typename T>
std::string serializeType(T obj) {
	std::stringstream ss;
	ss << obj;
	return ss.str();
}

template<>
inline std::string serializeType(const DirectX::Vector3& obj) {
	std::stringstream ss;
	ss << obj.x << ", " << obj.y << ", " << obj.z;
	return ss.str();
}

template<typename ComponentType>
void saveComponent(const ComponentType& component) {
	const auto& thing = typeid(ComponentType);
    auto classname = thing.name();
	std::string s(classname);
	if (boost::starts_with(s, "struct ")) {
		s = s.substr(strlen("struct "));
	} else {
		return;
	}
    
    visit_struct::for_each(component, [s](const auto& name, const auto& value) {
		std::cerr << name << ": " << serializeType<decltype(value)>(value) << "\n";
	});
}

#endif //HABANERO_CONSTRUCTORFUNCTIONS_H
