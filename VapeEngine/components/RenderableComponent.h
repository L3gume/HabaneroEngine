//
// Created by l3gume on 11/02/18.
//

#ifndef VAPEENGINE_RENDERABLECOMPONENT_H
#define VAPEENGINE_RENDERABLECOMPONENT_H

#include <VapeGL.h>
#include <ecs/ecs.h>
#include <render/PrimitiveShapes.h>
#include "TransformComponent.h"

// TODO: THIS IS A PLACEHOLDER, FIX WHEN NEW RENDERSYSTEM IS DONE

struct RenderableComponent : ECS::Component {
    explicit RenderableComponent(VapeRenderer::PrimitiveShapes _shape) {
        m_shape = _shape;
        switch (_shape) {
            case VapeRenderer::PrimitiveShapes::CUBE:
                m_modelPath = "../render/assets/cube/cube.obj";
                m_texturePath = "../render/assets/cube/cube.dds";
                break;
            case VapeRenderer::PrimitiveShapes::CYLINDER:
                break;
            case VapeRenderer::PrimitiveShapes::OCTAHEDRON:
                break;
            case VapeRenderer::PrimitiveShapes::PLANE:
                m_modelPath = "../render/assets/plane/plane.obj";
                m_texturePath = "../render/assets/plane/plane.dds";
                break;
            case VapeRenderer::PrimitiveShapes::PYRAMID:
                break;
            case VapeRenderer::PrimitiveShapes::SPHERE:
                break;
            default:
                m_modelPath = "";
                m_texturePath = "";
        }
    }

    VapeRenderer::PrimitiveShapes m_shape;

public:
    int getTextureID() {
        return textureID;
    }

    void setTextureID(int i) {
        textureID = i;
    }

    bool getLoaded() {
        return loaded;
    }

    void setLoaded(bool b) {
        loaded = b;
    }

    const char* getModelPath() {
        return m_modelPath;
    }

    const char *getTexturePath() {
        return m_texturePath;
    }

private:
    int textureID = -1;
    bool loaded = false;
    const char *m_modelPath = nullptr;
    const char *m_texturePath = nullptr;
};

#endif //VAPEENGINE_RENDERABLECOMPONENT_H
