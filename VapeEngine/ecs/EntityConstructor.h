//
// Created by l3gume on 15/02/18.
//

#ifndef VAPEENGINE_ENTITYCONSTRUCTOR_H
#define VAPEENGINE_ENTITYCONSTRUCTOR_H

#include "ecs.h"

namespace ECS {
    class EntityConstructor {
    public:
        EntityConstructor() = default;
        void constructEntity(std::vector<std::string> _args) noexcept;
        std::vector<std::string> loadFile(std::ifstream& _ifs);
    private:
//        void constructTransformComponent();
    };
}

#endif //VAPEENGINE_ENTITYCONSTRUCTOR_H
