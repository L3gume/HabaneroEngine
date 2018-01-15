//
// Created by notjustin on 12/31/17.
//

#include "Component.h"
#include "util.h"

/*
 * When deleting a component, delete all of its children. This is going to cause a "recursive" chain reaction of deleting
 * all the grand children. Make sure to always have as little references to components as possible to avoid null ptrs.
 */
Component::~Component() {
    for (Component* comp : m_children) {
        delete comp;
    }
}

/*
 * looks up for a component on the same hierarchy level
 */
template<typename T>
Component* Component::findComponent() {
    if (m_parent) {
        for (const auto comp : *(m_parent->getChildren())) {
            if (instanceOf<T>(comp)) {
                return comp;
            }
        }
    } else {
#if DEBUG
        VapeLog::LogManager::getInstance().printMessage(VapeLog::LogMessage(
                VapeLog::LogTag::GAME, VapeLog::LogType::WARNING,
                VapeLog::LogSeverity::MODERATE,
                "This object doesn't have a parent. Its either a mistake or a root object"));
#endif
    }
    return nullptr; // fail safe, also makes sure it doesn't crash if object doesn't have a parent
}

/*
 * looks up for a component in object's children
 */
template<typename T>
Component* Component::findComponentInChildren() {
    Component* ret = nullptr;
    for (const auto comp : m_children) {
        if (instanceOf<T>(comp)) {
            return comp;
        }
    }
    return ret;
}

/*
 * Recursively checks through all levels to find a component.
 * TODO: this has to be improved, right now, it is ridiculously slow
 */
template<typename T>
Component* Component::findComponentInChildrenSlow() {
    Component* ret = nullptr;
    for (const auto comp : m_children) {
        if (instanceOf<T>(comp)) {
            return comp;
        }
        ret = comp->findComponentInChildrenSlow<T>();
        if (ret) return ret;
    }
    return ret;
}