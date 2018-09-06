//
// Created by l3gume on 11/02/18.
//
#pragma once
#ifndef HABANERO_RENDERABLECOMPONENT_H
#define HABANERO_RENDERABLECOMPONENT_H

#include "engine/core/ecs/ecs.h"
#include "TransformComponent.h"

// TODO: THIS IS A PLACEHOLDER, FIX WHEN NEW RENDERSYSTEM IS DONE

/*
struct RenderableComponent : ecs::Component {
    explicit RenderableComponent(VapeRenderer::PrimitiveShapes _shape) {
        m_shape = _shape;
        switch (_shape) {
            case VapeRenderer::PrimitiveShapes::CUBE:
                std::copy(std::begin(VapeRenderer::cube_vertex_buffer_data), std::end(VapeRenderer::cube_vertex_buffer_data), std::begin(m_vBuf));
                std::copy(std::begin(VapeRenderer::cube_color_buffer_data), std::end(VapeRenderer::cube_color_buffer_data), std::begin(m_cBuf));
                break;
            case VapeRenderer::PrimitiveShapes::CYLINDER:
                break;
            case VapeRenderer::PrimitiveShapes::OCTAHEDRON:
                break;
            case VapeRenderer::PrimitiveShapes::PLANE:
                std::copy(std::begin(VapeRenderer::plane_vertex_buffer_data), std::end(VapeRenderer::plane_vertex_buffer_data), std::begin(m_vBuf));
                std::copy(std::begin(VapeRenderer::plane_color_buffer_data), std::end(VapeRenderer::plane_color_buffer_data), std::begin(m_cBuf));
                break;
            case VapeRenderer::PrimitiveShapes::PYRAMID:
                std::copy(std::begin(VapeRenderer::pyramid_vertex_buffer_data), std::end(VapeRenderer::pyramid_vertex_buffer_data), std::begin(m_vBuf));
                std::copy(std::begin(VapeRenderer::pyramid_color_buffer_data), std::end(VapeRenderer::pyramid_color_buffer_data), std::begin(m_cBuf));
                break;
            case VapeRenderer::PrimitiveShapes::SPHERE:
                break;
        }
    }
    GLfloat m_vBuf[1000];
    GLfloat m_cBuf[1000];
    VapeRenderer::PrimitiveShapes m_shape;
};
*/

#endif //HABANERO_RENDERABLECOMPONENT_H
