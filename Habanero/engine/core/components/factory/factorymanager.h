#pragma once
#ifndef ECS_FACTORYMANAGER_H
#define ECS_FACTORYMANAGER_H

#include <unordered_map>

#include "engine/core/util/singleton.h"
#include "engine/core/ecs/component.h"
#include "factory.h"

#define REGISTER_COMPONENT_FACTORY(name, class_name)\
    ecs::HComponentFactoryManager::getInstance().addComponentFactory<class_name>(name);

namespace ecs
{
    
class HComponentFactoryManager {
    HSINGLETON(HComponentFactoryManager) // Kinda evil, dunno
        
public:
    template <typename T>
    void addComponentFactory(const char* _name) {
        static_assert(std::is_base_of<Component, T>::value, "T must inherit from ecs::Component"); 
        assert(m_factories.find(_name) == m_factories.end());
        
        //IComponentFactory* factory = new HComponentFactory<T>();
        //m_factories[_name] = std::make_unique<IComponentFactory>(*factory);
        m_factories[_name] = new HComponentFactory<T>();
    }
    
    IComponentFactory* getComponentFactory(const char* _name) {
        assert(m_factories.find(_name) != m_factories.end());
        return m_factories[_name];
    }
    
private:
    std::unordered_map<const char*, IComponentFactory*> m_factories;
};

}
#endif
