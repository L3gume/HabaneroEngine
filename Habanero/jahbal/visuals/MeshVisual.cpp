#include "engine/core/ecs/ecs.h"
#include "engine/core/components/VisualComponent.h"
#include "jahbal/visuals/MeshVisual.h"
#include "jahbal/Mesh.h"

MeshVisual::MeshVisual(ECS::Entity* owner, JRenderer* renderer) 
	//: VisualComponent(owner, renderer, VisualType::MESH), m_Mesh(nullptr)
{

}

MeshVisual::~MeshVisual()
{

}

/*
void MeshVisual::CreateMesh(std::vector<MeshVertex> vertexList, std::vector<int> indexList)
{
	if (m_Mesh)
	{
		printf("WARNING: CREATEMESH CALLED WHEN MESH ALREADY EXISTS, MESH IS GOING TO BE OVERWRITTEN!");

		m_Mesh->OnDestroy();
		delete m_Mesh;
	}

	m_Mesh = new Mesh(this, vertexList, indexList);
}

void MeshVisual::CreateMesh(std::string filename)
{
	if (m_Mesh)
	{
		printf("WARNING: CREATEMESH CALLED WHEN MESH ALREADY EXISTS, MESH IS GOING TO BE OVERWRITTEN!");

		m_Mesh->OnDestroy();
		delete m_Mesh;
	}

	m_Mesh = new Mesh(this, filename);
}
*/

