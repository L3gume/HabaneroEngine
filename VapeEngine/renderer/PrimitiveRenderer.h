#ifndef VAPEENGINE_PRIMITIVERENDERER_H
#define VAPEENGINE_PRIMITIVERENDERER_H

#include "ObjectRenderer.h"
#include "PrimitiveShapes.h"

namespace VapeRenderer {
    class PrimitiveRenderer : public ObjectRenderer {
    public:
        PrimitiveRenderer(Component *_parent, PrimitiveShapes _shape);

        void render(GLuint* vertex_buf) override;

    private:
        PrimitiveShapes m_shape;

        void renderCube(GLuint* vertex_buf);
        void renderPlane(GLuint* vertex_buf);
    };
}

#endif //VAPEENGINE_PRIMITIVERENDERER_H
