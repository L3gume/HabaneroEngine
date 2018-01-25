#ifndef VAPEENGINE_MODELRENDERER_H
#define VAPEENGINE_MODELRENDERER_H

#include <patterns/Component.h>
#include <glm/vec3.hpp>
#include "ObjectRenderer.h"
#include "PrimitiveShapes.h"

namespace VapeRenderer {
    class ModelRenderer : public ObjectRenderer {
    public:
        explicit ModelRenderer(Core::GameObject *_parent);

        explicit ModelRenderer(Core::GameObject *_parent, char* _modelPath, char* _texturePath);

        void init(GLuint* _programID, GLuint* _textureID);

        bool isInit() {
            return b_init;
        }

        void render(GLuint* vertex_buf) override;

    private:
        bool b_init = false;

        char* m_modelPath;
        char* m_texturePath;

        GLuint* m_programID;

        GLuint m_texture;

        GLuint* m_textureID;

        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec2> m_uvs;
        std::vector<glm::vec3> m_normals;
    };
}

#endif //VAPEENGINE_MODELRENDERER_H
