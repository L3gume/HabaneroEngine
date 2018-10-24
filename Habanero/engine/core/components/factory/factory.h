#pragma once
#ifndef ECS_COMPONENTFACTORY_H
#define ECS_COMPONENTFACTORY_H

#include "engine/core/ecs/component.h"

class IComponentFactory {
public:
    virtual ecs::Component* make() = 0;
};

template <typename T>
class HComponentFactory : public IComponentFactory
{
public:
    HComponentFactory() = default;
    ecs::Component* make() override {
        return new T();
    }
};


#endif

