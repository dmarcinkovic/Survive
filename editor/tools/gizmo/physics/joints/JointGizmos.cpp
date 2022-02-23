//
// Created by david on 14. 02. 2022..
//

#include "JointGizmos.h"
#include "Maths.h"
#include "Util.h"
#include "Constants.h"

void Survive::JointGizmos::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::D))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
}

void Survive::JointGizmos::drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera)
{
}

void Survive::JointGizmos::mouseHoversAnchors(const ImVec2 &anchorA, const ImVec2 &anchorB, bool &anchorAHovered,
											  bool &anchorBHovered)
{
	if (!m_IsUsing && Util::mouseHoversPoint(anchorA, ANCHOR_RADIUS) && !anchorBHovered)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		anchorAHovered = true;
	} else if (!m_IsUsing && Util::mouseHoversPoint(anchorB, ANCHOR_RADIUS) && !anchorAHovered)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
		anchorBHovered = true;
	} else if (!m_IsUsing)
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		anchorAHovered = anchorBHovered = false;
	}
}

void Survive::JointGizmos::drawAnchorA(const ImVec2 &anchorPosition, bool isAnchorHovered)
{
	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = isAnchorHovered ? CIRCLE_COLOR_HOVERED : ANCHOR_COLOR;
	drawList->AddCircle(anchorPosition, ANCHOR_RADIUS, color, 0, 3.0f);
}

void Survive::JointGizmos::drawAnchorB(const ImVec2 &anchorPosition, bool isAnchorHovered)
{
	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = isAnchorHovered ? CIRCLE_COLOR_HOVERED : ANCHOR_COLOR;
	drawList->AddCircleFilled(anchorPosition, ANCHOR_RADIUS, color);
}

void Survive::JointGizmos::drawAnchorConnector(const ImVec2 &anchorA, const ImVec2 &anchorB)
{
	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddLine(anchorA, anchorB, ANCHOR_CONNECTOR_COLOR);
}

void Survive::JointGizmos::drawAnchors(const ImVec2 &anchorA, const ImVec2 &anchorB, bool anchorAHovered,
									   bool anchorBHovered)
{
	drawAnchorConnector(anchorA, anchorB);

	drawAnchorA(anchorA, anchorAHovered);
	drawAnchorB(anchorB, anchorBHovered);
}

std::tuple<glm::mat4, glm::vec3, float>
Survive::JointGizmos::getBodyTransform(entt::registry &registry, entt::entity body)
{
	if (body != entt::null && registry.all_of<Transform3DComponent>(body))
	{
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(body);
		glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

		float angle = glm::radians(transform.rotation.z);

		return {modelMatrix, transform.position, angle};
	}

	return {glm::mat4{1.0f}, glm::vec3{0.0f}, 0.0f};
}

void Survive::JointGizmos::updateAnchor(b2Vec2 &anchor, const Camera &camera, const glm::mat4 &modelMatrix,
										const glm::vec3 &position, float angle, bool isHovered) const
{
	if (m_IsUsing && isHovered)
	{
		ImVec2 mousePosition = ImGui::GetMousePos();

		glm::vec3 localPosition = Util::getLocalSpace(camera, modelMatrix, mousePosition, m_X, m_Y, m_Width,
													  m_Height);
		localPosition -= position;
		glm::vec3 rotatedAnchor = rotatePointAroundOrigin(localPosition.x, localPosition.y, -angle);

		glm::vec3 offset = rotatedAnchor * Constants::BOX2D_SCALE;
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

		anchor = b2Vec2(offset.x, offset.y);
	}
}

