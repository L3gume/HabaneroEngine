#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <glm/glm.hpp>

bool loadOBJ(
        const char * path,
        std::vector<glm::vec3> & out_vertices,
        std::vector<glm::vec2> & out_uvs,
        std::vector<glm::vec3> & out_normals
);

void load_obj(
        const char* filename,
        std::vector<glm::vec3> &vertices,
        std::vector<glm::vec2> &normals,
        std::vector<glm::vec3> &elements
);


#endif
