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
                m_modelPath = (std::string *) "../render/assets/cube/cube.obj";
                m_texturePath = (std::string *) "../render/assets/cube/uvmap.DDS";
                break;
            case VapeRenderer::PrimitiveShapes::CYLINDER:
                break;
            case VapeRenderer::PrimitiveShapes::OCTAHEDRON:
                break;
            case VapeRenderer::PrimitiveShapes::PLANE:
                break;
            case VapeRenderer::PrimitiveShapes::PYRAMID:
                break;
            case VapeRenderer::PrimitiveShapes::SPHERE:
                break;
            default:
                m_modelPath = (std::string *) "";
                m_texturePath = (std::string *) "";
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

    const std::string * getModelPath() {
        return m_modelPath;
    }

    const std::string *getTexturePath() {
        return m_texturePath;
    }

private:
    int textureID = -1;
    bool loaded = false;
    const std::string *m_modelPath = nullptr;
    const std::string *m_texturePath = nullptr;
};

#endif //VAPEENGINE_RENDERABLECOMPONENT_H
