#pragma once
#ifndef HABANERO_SCENECOMPONENT_H
#define HABANERO_SCENECOMPONENT_H

#include <utility>
#include "engine/core/ecs/component.h"
#include "libraries/visit_struct/visit_struct.hpp"
#include "engine/core/ecs/reflection/reflection.h"
#include "factory/factorymanager.h"

struct SceneComponent : ecs::Component {
    explicit SceneComponent(std::string _name) : name(std::move(_name)) {}
    std::string name;
};

VISITABLE_STRUCT(SceneComponent, name);

struct DummyComponent : ecs::Component {
    H_DECLARE_AS_REFLECTABLE(DummyComponent)
        
    DummyComponent() : m1(0), m2('\0'), m3(0.f), m4("") {}
    DummyComponent(int _m1, char _m2, float _m3, const char* _m4) : m1(_m1), m2(_m2), m3(_m3), m4(_m4) {}
    
    int m1;
    char m2;
    float m3;
    const char* m4;
};

H_DEFINE_NAMED_REFLECTION_DATA("DummyComponent", DummyComponent,
        H_ADD_NAMED_PROPERTY(m1, "member_1"),
        H_ADD_NAMED_PROPERTY(m2, "member_2"),
        H_ADD_NAMED_PROPERTY(m3, "member_3"),
        H_ADD_NAMED_PROPERTY(m4, "member_4")
)



#endif
