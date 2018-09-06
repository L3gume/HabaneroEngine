#include "entitymanager.h"
#include "EntityConstructor.h"

// This is to avoid a cyclical dependency issue and to work around the forward declared EntityManager in entity.h
void ecs::Entity::addGroup(Group _group) noexcept {
    m_groupBitset[_group] = true;
    m_manager->addToGroup(this, _group);
}

void ecs::EntityManager::loadEntity(const std::string& _path) {
    EntityConstructor constructor;
    std::ifstream ifs(_path);
    const auto args = constructor.loadFile(ifs);
    constructor.constructEntity(args, nullptr);
    ifs.close();
}
