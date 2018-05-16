#pragma once
#ifndef HABANERO_VISUALCOMPONENT_H
#define HABANERO_VISUALCOMPONENT_H

#include <vector>

#include "../ecs/ecs.h"
#include "../jahbal/renderers/JRenderer.h"

class Mesh;
class Material;

struct MeshVertex;

enum VisualType {MESH, BILLBOARD, TERRAIN};

struct VisualComponent : ECS::Component
{
	VisualComponent(Entity* owner, JRenderer* renderer, VisualType visualType);
	~VisualComponent() = default;
	void CreateMaterial();

	ID3D11Device* GetGFXDevice() { return m_Renderer->GetGFXDevice(); }
	
	Material* m_Material;
	JRenderer* m_Renderer;

	VisualType m_visualType;
};

VisualComponent::VisualComponent(Entity* owner, JRenderer* renderer, VisualType visualType) : m_visualType(visualType)
{
	m_Material = nullptr;

	m_Renderer = renderer;
}

void VisualComponent::CreateMaterial()
{
	if (m_Material)
	{
		printf("WARNING: CREATEMATERIAL CALLED WHEN MATERIAL ALREADY EXISTS, MATERIAL IS GOING TO BE OVERWRITTEN");

		delete m_Material;
	}

	//m_Material = new Material();
}

#endif
