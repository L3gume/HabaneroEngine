//
// Created by notjustin on 1/17/18.
//

#include "RigidBodyComponent.h"

#if EDITOR

/*
 * Displays the inspector section for the component
 */
void RigidBodyComponent::renderInspectorSection() {
    ImGui::Text("RigidBody Component:");
    ImGui::Text(" ");
    ImGui::InputFloat("Gravity Scale", &m_fGravityScale, 0.f, 0.f, 2);
    ImGui::Text("Lock Position:");
    ImGui::Checkbox("xPos", &m_bLockMovementX);
    ImGui::SameLine();
    ImGui::Checkbox("yPos", &m_bLockMovementY);
    ImGui::SameLine();
    ImGui::Checkbox("zPos", &m_bLockMovementZ);
    ImGui::Text("Lock Rotation:");
    ImGui::Checkbox("xRot", &m_bLockRotationX);
    ImGui::SameLine();
    ImGui::Checkbox("yRot", &m_bLockRotationY);
    ImGui::SameLine();
    ImGui::Checkbox("zRot", &m_bLockRotationZ);
    ImGui::Text("Is Kinematic:");
    ImGui::SameLine();
    ImGui::Checkbox("isKin", &m_bKinematic);
    ImGui::Separator();
}

#endif