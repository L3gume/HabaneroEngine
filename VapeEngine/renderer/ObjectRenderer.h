#ifndef VAPEENGINE_OBJECTRENDERER_H
#define VAPEENGINE_OBJECTRENDERER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <patterns/Component.h>

namespace VapeRenderer {
    //
    // Base render object. Abstract so only header file.
    //
    class ObjectRenderer : public Component {
    public:
        explicit ObjectRenderer(Component* _parent) : Component(_parent) {}
        /* Uses the destructor from the Component class */

        virtual void render(GLuint* vertex_buf) = 0;
    };
}

#endif //VAPEENGINE_OBJECTRENDERER_H
