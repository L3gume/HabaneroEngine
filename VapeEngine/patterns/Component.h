//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_COMPONENT_H
#define VAPEENGINE_COMPONENT_H


#include <vector>
#include <common/util.h>
#include "LogMessage.h"
#include "LogManager.h"

class Component {
public:
    explicit Component(Component* _parent = nullptr) : m_parent(_parent) {};
    /*
     * When deleting a component, delete all of its children. This is going to cause a "recursive" chain reaction of deleting
     * all the grand children. Make sure to always have as little references to components as possible to avoid null ptrs.
     */
    ~Component() {
//        for (auto comp : m_children) {
//            delete comp;
//        }
    }

    void addComponent(Component* _component) {
        m_children.emplace_back(_component);
        if (_component->m_parent != this) {
            _component->setParent(this); // Just in case.
        }
    }
    std::vector<Component*>* getChildren() { return &m_children; }
    void setParent(Component* _parent) { m_parent = _parent; }  // Does not delete the old parent,
                                                                // programmer is responsible for this
    Component* getParent() { return m_parent; }

    template<typename T>
    T* findComponentInParent() {
        if (m_parent) {
            for (Component* comp : *(m_parent->getChildren())) {
                if (instanceOf<T>(comp)) {
                    return static_cast<T*>(comp);
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
    } // will NOT go through children, looks up on same level as current object

    template<typename T>
    T* findComponent() {
        for (Component* comp : m_children) {
            if (instanceOf<T>(comp)) {
                return static_cast<T*>(comp);
            }
        }
        return nullptr;
    } // will go through direct children

    template<typename T>
    T* findComponentInChildrenSlow() {
        T* ret = nullptr;
        for (Component* comp : m_children) {
            if (instanceOf<T>(comp)) {
                return comp;
            }
            ret = comp->findComponentInChildrenSlow<T>();
            if (ret) return ret;
        }
        return nullptr;
    } // will go through the whole hierarchy, will be much slower.

protected:
    Component* m_parent;
    std::vector<Component*> m_children;
};


#endif //VAPEENGINE_COMPONENT_H
