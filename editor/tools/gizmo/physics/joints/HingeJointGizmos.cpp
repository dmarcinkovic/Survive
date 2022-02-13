//
// Created by david on 24. 01. 2022..
//

#include "HingeJointGizmos.h"
#include "Maths.h"
#include "Util.h"
#include "Constants.h"

bool Survive::HingeJointGizmos::m_AnchorAHovered{};
bool Survive::HingeJointGizmos::m_AnchorBHovered{};

void Survive::HingeJointGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity == entt::null)
	{
		m_GizmoEnabled = false;
	}

	if (selectedEntity != entt::null && registry.all_of<HingeJoint2DComponent, Transform3DComponent>(selectedEntity))
	{
		if (m_GizmoEnabled)
		{
			m_IsUsing = ImGui::IsMouseDragging(ImGuiMouseButton_Left);

			drawGizmos(registry, selectedEntity, camera);
		}
	}
}

bool Survive::HingeJointGizmos::isOver()
{
	return m_AnchorAHovered || m_AnchorAHovered;
}

void Survive::HingeJointGizmos::handleKeyEvents(const Survive::EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::D))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
}

void Survive::HingeJointGizmos::drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera)
{
	HingeJoint2DComponent &hingeComponent = registry.get<HingeJoint2DComponent>(bodyA);
	b2RevoluteJointDef &jointDef = hingeComponent.jointDef;

	ImVec2 anchorA = getAnchorPosition(registry, bodyA, camera, jointDef.localAnchorA);
	ImVec2 anchorB = getAnchorPosition(registry, hingeComponent.connectedBody, camera, jointDef.localAnchorB);

	mouseHoversAnchors(anchorA, anchorB);

	drawAnchorConnector(anchorA, anchorB);
	drawAnchorA(anchorA);
	drawAnchorB(anchorB);
}

void Survive::HingeJointGizmos::drawAnchorA(const ImVec2 &anchorPosition)
{
	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = m_AnchorAHovered ? CIRCLE_COLOR_HOVERED : ANCHOR_COLOR;
	drawList->AddCircle(anchorPosition, ANCHOR_RADIUS, color, 0, 3.0f);
}

void Survive::HingeJointGizmos::drawAnchorB(const ImVec2 &anchorPosition)
{
	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = m_AnchorBHovered ? CIRCLE_COLOR_HOVERED : ANCHOR_COLOR;
	drawList->AddCircleFilled(anchorPosition, ANCHOR_RADIUS, color);
}

ImVec2 Survive::HingeJointGizmos::getAnchorPosition(entt::registry &registry, entt::entity body, const Camera &camera,
													const b2Vec2 &anchor)
{
	if (body != entt::null && registry.all_of<Transform3DComponent>(body))
	{
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(body);
		glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

		float angle = glm::radians(transform.rotation.z);

		return getPoint(transform.position, anchor, camera, modelMatrix, angle);
	}

	return getPoint(glm::vec3{0.0f}, anchor, camera, glm::mat4{1.0f}, 0.0f);
}

void Survive::HingeJointGizmos::drawAnchorConnector(const ImVec2 &anchorA, const ImVec2 &anchorB)
{
	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddLine(anchorA, anchorB, ANCHOR_CONNECTOR_COLOR);
}

void Survive::HingeJointGizmos::mouseHoversAnchors(const ImVec2 &anchorA, const ImVec2 &anchorB)
{
	if (!m_IsUsing && Util::mouseHoversPoint(anchorA, ANCHOR_RADIUS) && !m_AnchorBHovered)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		m_AnchorAHovered = true;
	} else if (!m_IsUsing && Util::mouseHoversPoint(anchorB, ANCHOR_RADIUS) && !m_AnchorAHovered)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		m_AnchorBHovered = true;
	} else if (!m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		m_AnchorAHovered = m_AnchorBHovered = false;
	}
}
