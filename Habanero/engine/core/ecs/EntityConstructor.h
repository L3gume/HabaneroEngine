//
// Created by l3gume on 15/02/18.
//
#pragma once
#ifndef HABANERO_ENTITYCONSTRUCTOR_H
#define HABANERO_ENTITYCONSTRUCTOR_H

#include "ecs.h"
#include "engine/core/components/TransformComponent.h"
#include "engine/core/components/RenderableComponent.h"
#include "engine/core/components/CameraComponent.h"
#include "engine/core/components/ScriptComponent.h"
#include "engine/core/Engine.h"
#include "EntityConstructor.h"

namespace ecs {
    class EntityConstructor {
    public:
        EntityConstructor() = default;
        void constructEntity(std::vector<std::string> _args, /*const std::shared_ptr<Entity>&*/ Entity* _parent) noexcept;
        std::vector<std::string> loadFile(std::ifstream& _ifs);

        void saveEntityFile(Entity& _ent, std::string _filename);
        void saveEntity(Entity& _ent, std::ostringstream* _oss);
    private:
//        void constructTransformComponent();
    };
}

#endif //HABANERO_ENTITYCONSTRUCTOR_H
