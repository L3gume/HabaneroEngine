#pragma once
#include <vector>

class Mesh;
class SubMesh;
struct MeshVertex;

class MeshCreator {
public:
    MeshCreator() = default;
    ~MeshCreator() = default;

    static Mesh* createMesh(std::vector<MeshVertex> vertexList, std::vector<int> indexList);
    static Mesh* createMesh(std::string filename);
};