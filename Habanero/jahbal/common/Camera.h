#pragma once

#include <d3d11.h>

#include "libraries/DirectXTK/include/SimpleMath.h"

namespace jahbal {

class Camera
{
public:
	Camera(float radius, DirectX::SimpleMath::Vector3 target);
	Camera(float radius);
	Camera();

	void Update(float dt);

	DirectX::SimpleMath::Matrix GetLookAtMatrix();
	void UpdatePosition();

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_target;

	float m_Phi;
	float m_Theta;
	float m_Radius;
	int m_moveSpeed;
};

}  // namespace jahbal