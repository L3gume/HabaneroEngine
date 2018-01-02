#ifndef VAPEENGINE_PRIMITIVERENDERER_H
#define VAPEENGINE_PRIMITIVERENDERER_H

#include "ObjectRenderer.h"
#include "PrimitiveShapes.h"

namespace VapeRenderer {
    class PrimitiveRenderer : public ObjectRenderer {
    public:
        PrimitiveRenderer(Core::GameObject* _parent, PrimitiveShapes _shape);

        void render() override;

    private:
        PrimitiveShapes m_shape;

        void renderCube();
        void renderPlane();
    };
}

#endif //VAPEENGINE_PRIMITIVERENDERER_H
