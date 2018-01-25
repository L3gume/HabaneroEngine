//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_GAMEOBJECT_H
#define VAPEENGINE_GAMEOBJECT_H

#include <vector>
#include <glm/vec3.hpp>
#include <common/util.h>
#include <logging/LogManager.h>

class Component;

namespace Core {

    struct Transform {
        glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
    };

    class GameObject {
    public:
        explicit GameObject(GameObject *_parent) { /* nothing special for now */ }

        /* Uses the destructor from the Component class */
        inline Transform *getAbsTransform() { return &m_absoluteTransform; }
        inline Transform *getTransform() { return &m_transform; } // returns a pointer to the transform in order
        // to make it easy to modify

        inline void setParent(GameObject* _parent) { m_parent = _parent; }
        inline GameObject* getParent() const { return m_parent; }

        virtual void init() { /* Meant to be overriden */ }
        virtual void update(const float _deltaTime);

        void addChild(GameObject* _child);
        GameObject* findChildByTag(const std::string _tag);
        GameObject* findChildByID(const int _id);
        std::vector<GameObject*>* getChildren() { return &m_children; }

        void addComponent(Component *_component);
        std::vector<Component *> *getComponents() { return &m_components; }

        template<typename T>
        T *findComponentInParent() {
            if (m_parent) {
                for (Component *comp : *(m_parent->getComponents())) {
                    if (instanceOf<T>(comp)) {
                        return static_cast<T *>(comp);
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
        T *findComponent() {
            for (Component *comp : m_components) {
                if (instanceOf<T>(comp)) {
                    return static_cast<T *>(comp);
                }
            }
            return nullptr;
        } // will go through direct children

        template<typename T>
        T *findComponentInChildren() {
            T *ret = nullptr;
            for (GameObject *go : m_children) {
                for (Component *comp : *(go->getComponents())) {
                    if (instanceOf<T>(comp)) {
                        return comp;
                    }
                }
                if (ret = go->findComponentInChildren<T>(); ret) {
                    return ret;
                }
            }
            return nullptr;
        } // will go through the whole hierarchy, will be much slower.


        inline int getID() const { return m_id; }
        inline std::string getTag() const { return m_tag; }
        std::string m_tag = ""; // name given to the object
    protected:
        std::vector<Component *> m_components;
        std::vector<GameObject *> m_children;
        GameObject *m_parent;

        Transform m_transform;
        Transform m_absoluteTransform;
        int m_id = 0;
    };
}

class Component {
public:
    explicit Component(Core::GameObject* _parent = nullptr) : m_parent(_parent) {};
    /*
     * When deleting a component, delete all of its children. This is going to cause a "recursive" chain reaction of deleting
     * all the grand children. Make sure to always have as little references to components as possible to avoid null ptrs.
     */
    ~Component() {}

    void setParent(Core::GameObject* _parent) { m_parent = _parent; }  // Does not delete the old parent,
    // programmer is responsible for this
    Core::GameObject* getParent() { return m_parent; }

protected:
    Core::GameObject* m_parent;
};


#endif //VAPEENGINE_GAMEOBJECT_H
