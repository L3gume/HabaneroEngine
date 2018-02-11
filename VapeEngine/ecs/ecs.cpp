//
// Created by notjustin on 2/9/18.
//

#include <ecs.h>

using namespace ECS;

// This one had to be in a .cpp file because of the forward declaration
void Entity::addGroup(Group _group) noexcept {
    m_groupBitset[_group] = true;
    m_manager->addToGroup(this, _group);
}

