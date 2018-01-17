//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_COMPONENT_H
#define VAPEENGINE_COMPONENT_H


#include <vector>
#include "LogMessage.h"
#include "LogManager.h"

class Component {
public:
    explicit Component(Component* _parent = nullptr) : m_parent(_parent) {};
    ~Component();

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
    Component* findComponent(); // will NOT go through children, looks up on same level as current object

    template<typename T>
    Component* findComponentInChildren(); // will go through direct children

    template<typename T>
    Component* findComponentInChildrenSlow(); // will recursively go through the whole hierarchy, will be much slower.

protected:
    Component* m_parent;
    std::vector<Component*> m_children;
};


#endif //VAPEENGINE_COMPONENT_H
