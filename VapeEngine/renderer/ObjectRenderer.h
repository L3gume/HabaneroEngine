#ifndef VAPEENGINE_OBJECTRENDERER_H
#define VAPEENGINE_OBJECTRENDERER_H

#include "VapeGL.h"
#include <core/GameObject.h>

namespace VapeRenderer {
    //
    // Base render object. Abstract so only header file.
    //
    class ObjectRenderer : public Component {
    public:
        explicit ObjectRenderer(Core::GameObject* _parent) : Component(_parent) {}
        /* Uses the destructor from the Component class */

        virtual void render(GLuint* vertex_buf) {}
    };
}

#endif //VAPEENGINE_OBJECTRENDERER_H
