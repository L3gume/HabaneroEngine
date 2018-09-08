//
// Created by l3gume on 19/02/18.
//
#pragma once
#ifndef HABANERO_CONSTRUCTORFUNCTIONS_H
#define HABANERO_CONSTRUCTORFUNCTIONS_H

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

#endif //HABANERO_CONSTRUCTORFUNCTIONS_H
