//
// Created by l3gume on 15/02/18.
//

#ifndef HABANERO_ENTITYCONSTRUCTOR_H
#define HABANERO_ENTITYCONSTRUCTOR_H

#include "ecs.h"
#include "../components/TransformComponent.h"
#include "../components/RenderableComponent.h"
#include "../components/CameraComponent.h"
#include "../components/ScriptComponent.h"
#include "../script/PlayerMovementScript.h"
#include "../core/Engine.h"
#include "EntityConstructor.h"

namespace ECS {
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
