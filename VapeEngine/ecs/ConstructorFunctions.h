//
// Created by l3gume on 19/02/18.
//

#ifndef VAPEENGINE_CONSTRUCTORFUNCTIONS_H
#define VAPEENGINE_CONSTRUCTORFUNCTIONS_H

#include <ecs/ecs.h>
#include <TransformComponent.h>
#include <glm/glm.hpp>
#include <render/PrimitiveShapes.h>
#include <components/RenderableComponent.h>
#include <components/CameraComponent.h>
#include <components/ScriptComponent.h>
#include <script/PlayerMovementScript.h>
#include <VapeGL.h>

using namespace ECS;

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

#endif //VAPEENGINE_CONSTRUCTORFUNCTIONS_H
