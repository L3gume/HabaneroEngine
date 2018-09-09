#include "Camera.h"

#include "libraries/DirectXTK/include/SimpleMath.h"

namespace jahbal {

Camera::Camera(float radius, DirectX::SimpleMath::Vector3 target)
{
	m_Phi = 0;
	m_Theta = 0;
	m_Radius = radius;
	m_moveSpeed = 5;

	UpdatePosition();
	m_target = target;
}

Camera::Camera(float radius) : Camera(radius, DirectX::SimpleMath::Vector3::Zero) {}

Camera::Camera() : Camera(20.0, DirectX::SimpleMath::Vector3::Zero) {}

void Camera::Update(float dt)
{
	/*
	auto kb = InputManager::GetInstance()->m_Keyboard->GetState();

	float phi = m_Phi;
	float theta = m_Theta;
	float radius = m_Radius;
	if (kb.Up || kb.W)
		phi += 0.0005f * dt * m_moveSpeed;
	if (kb.Down || kb.S)
		phi -= 0.0005f * dt * m_moveSpeed;
	if (kb.Left || kb.A)
		theta -= 0.0005f * dt * m_moveSpeed;
	if (kb.Right || kb.D)
		theta += 0.0005f * dt * m_moveSpeed;
	if (kb.OemPlus) radius += 0.01f * dt * m_moveSpeed;
	if (kb.OemMinus) radius -= 0.01f * dt * m_moveSpeed;

	radius = radius < 1.0 ? 1.0f : radius;
	phi = phi >(3.14f / 2.0f) ? (3.14f / 2.0f) : (phi < -(3.14f / 2.0f) ? -(3.14f / 2.0f) : phi);
	m_Phi = phi; m_Theta = theta; m_Radius = radius;
	UpdatePosition();
	*/
}

void Camera::UpdatePosition()
{
	m_position = DirectX::SimpleMath::Vector3(m_Radius * cosf(m_Phi) * cosf(m_Theta),
		m_Radius * sinf(m_Phi),
		m_Radius * cosf(m_Phi) * sinf(m_Theta));
}
DirectX::SimpleMath::Matrix Camera::GetLookAtMatrix()
{
	return DirectX::SimpleMath::Matrix::CreateLookAtLH(
		DirectX::SimpleMath::Vector3(m_position),
		DirectX::SimpleMath::Vector3(m_target),
		DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
}

}  // namespace jahbal

