#ifndef VAPEENGINE_OBJECTRENDERER_H
#define VAPEENGINE_OBJECTRENDERER_H

#include "GameObject.h"

namespace VapeRenderer {
    //
    // Base render object. Abstract so only header file.
    //
    class ObjectRenderer {
    public:
        ObjectRenderer(Core::GameObject* _parent) {
            //Constructor
            this->m_parent = _parent;
        }

        virtual void render(GLuint* vertex_buf) = 0;

    protected:
        Core::GameObject* m_parent;
    };
}

#endif //VAPEENGINE_OBJECTRENDERER_H
