//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_GAMEOBJECT_H
#define VAPEENGINE_GAMEOBJECT_H

#include <glm/vec3.hpp>
#include <renderer/ObjectRenderer.h>
#include "Component.h"

namespace Core {

    struct Transform {
        glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 scale    = glm::vec3(1.f, 1.f, 1.f);
    };

    class GameObject : public Component {
    public:
        explicit GameObject(Component* _parent, VapeRenderer::ObjectRenderer* _renderer) : Component(_parent) {
            m_renderer = _renderer;
        }
        /* Uses the destructor from the Component class */

        inline Transform* getTransform() { return &m_transform; } // returns a pointer to the transform in order
                                                                  // to make it easy to modify
        inline VapeRenderer::ObjectRenderer* getRenderer() { return m_renderer; }
    private:
        Transform m_transform;
        VapeRenderer::ObjectRenderer* m_renderer;

        int m_id;
        std::string m_tag; // name given to the object
    };
}
#endif //VAPEENGINE_GAMEOBJECT_H
