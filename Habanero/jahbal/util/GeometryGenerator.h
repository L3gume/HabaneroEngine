#pragma once
#include <vector>
#include <string>
#include <DirectXMath.h>
#include <d3d11.h>

#include "DirectXTK\include\SimpleMath.h"
#include "jahbal/Mesh.h"

using namespace DirectX;

struct MeshVertex;

class GeometryGenerator
{
public:

	static void CreatePlane(float width, float length, std::vector<MeshVertex>& v, std::vector<int>& i);
	static void CreateBox(float width, float height, float depth, std::vector<MeshVertex>& vertices, std::vector<int>&  indices);
};