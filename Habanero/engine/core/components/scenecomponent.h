#pragma once
#ifndef HABANERO_SCENECOMPONENT_H
#define HABANERO_SCENECOMPONENT_H

#include <utility>
#include "engine/core/ecs/component.h"
#include "libraries/visit_struct/visit_struct.hpp"

struct SceneComponent : ecs::Component {
    explicit SceneComponent(std::string _name) : name(std::move(_name)) {}
    std::string name;
};

VISITABLE_STRUCT(SceneComponent, name);

#endif
