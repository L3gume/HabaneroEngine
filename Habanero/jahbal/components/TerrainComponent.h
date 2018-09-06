#pragma once
#include <DirectXMath.h>
#include <d3d11.h>

#include "libraries/DirectXTK/include/SimpleMath.h"
#include "engine/core/ecs/component.h"
#include "engine/core/components/VisualComponent.h"

class JTerrain;
class JRenderer;

using namespace DirectX;

struct TerrainVertex
{
	TerrainVertex(float px, float py, float pz)
		: position(px, py, pz) {}
	TerrainVertex()
		: position(0.0f, 0.0f, 0.0f) {}

	Vector3 position;
	Vector2 textureCoord;
	Vector2 boundsY;
};

struct TerrainInfo
{
	TerrainInfo(std::wstring file, UINT w, UINT h, float scale, float cSpacing)
		: heightMapFileName(file), width(w), height(h), heightScale(scale), cellSpacing(cSpacing) {}
	
	std::wstring heightMapFileName;

	UINT width;
	UINT height;

	float heightScale;
	float cellSpacing;
};


struct TerrainComponent : public ecs::Component
{
public:
	TerrainComponent(ecs::Entity* owner, JRenderer* renderer, TerrainInfo info);
	~TerrainComponent();

	//void SetupBuffers();
	//void InitHeightMap();
	//void InitHeightMapSRV();

	float GetWidth() const { return (m_terrainInfo.width - 1) * m_terrainInfo.cellSpacing; }
	float GetDepth() const { return (m_terrainInfo.height - 1) * m_terrainInfo.cellSpacing; }

	JTerrain* m_JTerrain;
	ID3D11Buffer* m_VB;
	ID3D11Buffer* m_IB;
	ID3D11ShaderResourceView* m_heightMapSRV;

	TerrainInfo m_terrainInfo;
	std::vector<float> m_heightMapData;
	std::vector<TerrainVertex> m_vertices;

	static const int sCellsPerPatch = 64; // max tesselation factor in dx11 is 64
	int m_numPatchRows;
	int m_numPatchCols;
	int m_numPatchVertices;
	int m_numPatchQuadFaces;

private:
	//void SmoothHeightMap();
	//float ComputeHeightAverage(int x, int y);
	//boolean isWithinHeightMap(int i , int j);

	//void InitVB();
	//void InitIB();
};
