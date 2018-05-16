#pragma once

#include <vector>
#include <string>
#include <DirectXMath.h>
#include <d3d11.h>

#include "../libraries/assimp/include/Importer.hpp"
#include "../libraries/assimp/include/scene.h"
#include "../libraries/assimp/include/postprocess.h"
#include "../libraries/DirectXTK/include/SimpleMath.h"

class SubMesh;

struct VisualComponent;
struct MeshVertex;

using namespace DirectX;

struct Texture
{
	unsigned int ID;
	std::string Type;
};

class Mesh
{
public:
	Mesh(VisualComponent* owner, std::vector<MeshVertex> vertexList, std::vector<int> indexList);
	Mesh(VisualComponent* owner, std::string filename);
	~Mesh();

	void OnDestroy();

	std::vector<SubMesh> m_subMeshList;
	std::string m_meshFullPath;
	VisualComponent* m_componentOwner;


private:
	bool createSRVFromAssimpMat(aiMaterial* mat, aiTextureType type, ID3D11ShaderResourceView** srv);
	void processMesh(aiMesh* mesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene);
	std::string getFolderFromFullPath(std::string path); //TODO put this in a util class maybe

	std::string m_meshFolder;
};

