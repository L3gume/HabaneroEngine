//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_GAMEOBJECT_H
#define VAPEENGINE_GAMEOBJECT_H

#include <glm/vec3.hpp>
#include <renderer/ObjectRenderer.h>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <patterns/Component.h>

namespace Core {

    struct Transform {
        glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 euler_rotation = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);

        inline glm::quat getQuatRotation() { return glm::quat(euler_rotation); }
    };

    class GameObject : public Component {
    public:
        explicit GameObject(Component* _parent) : Component(_parent) {}
        /* Uses the destructor from the Component class */
        inline Transform* getAbsTransform() { return &m_absoluteTransform; }
        inline Transform* getTransform() { return &m_transform; } // returns a pointer to the transform in order
                                                                  // to make it easy to modify

        virtual void init() { /* Meant to be overriden */ }
        virtual void update(const float _deltaTime);
        /*
         * TODO: the children's position, rotation and scale and offsets of the parent's.
         */

        inline int getID() const { return m_id; }
        inline std::string getTag() const { return m_tag; }

        std::string m_tag = ""; // name given to the object
    protected:
        Transform m_transform;
        Transform m_absoluteTransform;
        int m_id = 0;
    };
}
#endif //VAPEENGINE_GAMEOBJECT_H
