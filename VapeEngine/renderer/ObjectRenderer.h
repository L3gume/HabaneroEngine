#ifndef VAPEENGINE_OBJECTRENDERER_H
#define VAPEENGINE_OBJECTRENDERER_H

#include <GL/glew.h>
#include <GL/gl.h>

namespace VapeRenderer {
    //
    // Base render object. Abstract so only header file.
    //
    class ObjectRenderer {
    public:
        ObjectRenderer() {
            //Constructor
        }

        virtual void render(GLuint* vertex_buf) = 0;
    };
}

#endif //VAPEENGINE_OBJECTRENDERER_H
