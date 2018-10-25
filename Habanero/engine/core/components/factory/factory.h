#pragma once
#ifndef ECS_COMPONENTFACTORY_H
#define ECS_COMPONENTFACTORY_H

#include "engine/core/ecs/component.h"

namespace ecs
{

class IComponentFactory {
public:
    virtual Component* make() const = 0;
    virtual ComponentID getID() const = 0;
    virtual ~IComponentFactory() = default;
};

template <typename T>
class HComponentFactory : public IComponentFactory
{
public:
    HComponentFactory() = default;
    T* make() const override {
        return new T();
    }

    ComponentID getID() const override {
        return getComponentTypeID<T>();
    }
};

}
#endif

