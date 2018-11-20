#include "xmlentityserializer.h"
#include "engine/core/components/scenecomponent.h"
#include "engine/core/util/tree.h"

void ecs::HXmlEntitySerializer::saveScene(const Entity* _sceneEntity) const {
    if (!_sceneEntity->hasComponent<SceneComponent>()) {
        return;
    }
    const auto& sceneComp = _sceneEntity->getComponent<SceneComponent>();
    writeEntityToFile(sceneComp.name + ".entity", serializeEntity(_sceneEntity));
}

ecs::SSerializedEntity ecs::HXmlEntitySerializer::serializeEntity(const Entity* _ent, const std::string& _indent) const {
    const auto& components = _ent->m_components;
    const auto& children = _ent->getChildren();
    const auto tab = _indent + "    ";
    
    TTree<std::string> tree("test");
    tree.root().addChild("test1");
    
    SSerializedEntity serializedEnt;
    serializedEnt.name = _ent->m_sName;
    /*
     * TODO: Find a way to simplify that, typenames or typeids maybe?
     */
    //if (_ent->hasComponent<SceneComponent>()) {
    //    serializedEnt.components.emplace_back(serializeComponent(_ent->getComponent<SceneComponent>(), tab));
    //}
    //if (_ent->hasComponent<TransformComponent>()) {
    //    serializedEnt.components.emplace_back(serializeComponent(_ent->getComponent<TransformComponent>(), tab));
    //}
    for (const auto& comp : components) {
        serializedEnt.components.emplace_back(serializeComponent(*comp, tab));
    }
    
    for (const auto& child : children) {
        serializedEnt.children.emplace_back(serializeEntity(child, tab));
    }
    return serializedEnt;
}

void ecs::HXmlEntitySerializer::writeEntityToFile(const std::string& _filename, const SSerializedEntity& _ent) {
    std::ofstream of(_filename);
    of << _ent.toString() << "\n";
    of.close();
}
