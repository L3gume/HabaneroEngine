#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <memory>

#include "libraries/DirectXTK/include/SimpleMath.h"
#include "engine/core/ecs/component.h"
#include "engine/core/components/VisualComponent.h"
#include "jahbal/Mesh.h"

class JRenderer;
class Mesh;
class RenderSystem;

using namespace DirectX;

struct MeshVertex
{
	MeshVertex(float px, float py, float pz, float nx, float ny, float nz, float u, float v)
		: position(px, py, pz), normal(nx, ny, nz), uv(u, v) {}
	MeshVertex() : position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f) {}

	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 normal;
	DirectX::SimpleMath::Vector2 uv;
};

// TODO remove unneeded mesh vertex copies
struct MeshComponent : public ecs::Component
{
	MeshComponent(const std::vector<MeshVertex>& vertexList, const std::vector<int>& indexList) : 
        m_vertexList(vertexList), m_Mesh(new Mesh(vertexList, indexList)) {}
	MeshComponent(const std::string& filename) :
		m_Mesh(new Mesh(filename)) {}

	~MeshComponent() {}

	std::unique_ptr<Mesh> m_Mesh;
    std::vector<MeshVertex> m_vertexList;
};

