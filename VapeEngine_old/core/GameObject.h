//
// Created by notjustin on 12/31/17.
//

#ifndef HABANERO_GAMEOBJECT_H
#define HABANERO_GAMEOBJECT_H

#include <vector>
#include "glm/vec3.hpp"
//#include <common/util.h>
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "../logging/LogManager.h"

class deprecatedComponent;

namespace Core {

    struct Transform {
        glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 euler_rotation = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
        inline glm::quat getQuatRotation() const { return glm::quat(euler_rotation); }
    };

    class GameObject {
    public:
        explicit GameObject(GameObject *_parent) : m_parent(_parent) { m_id = generateUniqueID(); }

        inline Transform *getTransform() { return &m_transform; } // returns a pointer to the transform in order
        // to make it easy to modify

        inline void setParent(GameObject* _parent) { m_parent = _parent; }
        inline GameObject* getParent() const { return m_parent; }

        virtual void init() { /* Meant to be overriden */ }
        virtual void update(float _deltaTime);

        void addChild(GameObject* _child);
        std::vector<GameObject*>* getChildren() { return &m_children; }

        void addComponent(deprecatedComponent *_component);
        std::vector<deprecatedComponent *> *getComponents() { return &m_components; }

        inline int getID() const { return m_id; }
        inline std::string getTag() const { return m_tag; }

        std::string m_tag = ""; // name given to the object

        /*
         * Templated member functions, those have to be declared and defined in the header.
         */
        // Takes a comparison lambda so that you can use whatever you like to find the child.
        template<typename Func>
        GameObject* findChild(Func _f) {
            const auto found = std::find_if(m_children.begin(), m_children.end(), _f);
            return found != m_children.end() ? *found : nullptr;
        }

        template<typename T>
        T *findComponentInParent() {
            if (m_parent) {
                for (deprecatedComponent *comp : *(m_parent->getComponents())) {
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
            for (deprecatedComponent *comp : m_components) {
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
                for (deprecatedComponent *comp : *(go->getComponents())) {
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
    protected:
        std::vector<deprecatedComponent *> m_components;
        std::vector<GameObject *> m_children;
        GameObject *m_parent;

        Transform m_transform;
        int m_id = 0;
    };
}

class deprecatedComponent {
public:
    explicit deprecatedComponent(Core::GameObject* _parent = nullptr) : m_parent(_parent) {};
    /*
     * When deleting a component, delete all of its children. This is going to cause a "recursive" chain reaction of deleting
     * all the grand children. Make sure to always have as little references to components as possible to avoid null ptrs.
     */
    ~deprecatedComponent() = default;

    void setParent(Core::GameObject* _parent) { m_parent = _parent; }  // Does not delete the old parent,
    // programmer is responsible for this
    Core::GameObject* getParent() { return m_parent; }

#if EDITOR
    virtual void renderInspectorSection() {}
#endif

protected:
    Core::GameObject* m_parent;
};


#endif //HABANERO_GAMEOBJECT_H
