//
// Created by notjustin on 12/31/17.
//
#include "GameObject.h"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtx\quaternion.hpp"

using namespace Core;

void GameObject::update(const float _deltaTime) {}

void GameObject::addComponent(deprecatedComponent *_component) {
    m_components.emplace_back(_component);
    if (_component->getParent() != this) {
        _component->setParent(this); // Just in case
    }
}

void GameObject::addChild(GameObject *_child) {
    /*
     * Start by looking up the children list to make we don't add duplicate objects
     */
    bool _found = false;
    // C++14 lambda initialization capture :D
    GameObject* found = findChild([_id = _child->getID()] (const GameObject* _obj) {
        return _obj->getID() == _id;
    });
    _found = found != nullptr;
    /*
     * If it wasn't found, add it to children.
     */
    if (!_found) {
        _child->setParent(this); // Just in case
        m_children.emplace_back(_child);
    } else {
        // Does nothing in release build!
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::GAME, VapeLog::LogType::WARNING,
                VapeLog::LogSeverity::MODERATE,
                "This object is already a child, it was not added."));
#endif
    }
}
