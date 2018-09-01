#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <memory>

#include "libraries/DirectXTK/include/SimpleMath.h"
#include "engine/core/ecs/ecs.h"
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

	Vector3 position;
	Vector3 normal;
	Vector2 uv;
};


class MeshVisual : public ECS::Component
{
public:
	MeshVisual(const std::vector<MeshVertex>& vertexList, const std::vector<int>& indexList) : 
		m_Mesh(new Mesh(vertexList, indexList)) {}
	MeshVisual(const std::string& filename) :
		m_Mesh(new Mesh(filename)) {}

	~MeshVisual() {}

	std::unique_ptr<Mesh> m_Mesh;
};

