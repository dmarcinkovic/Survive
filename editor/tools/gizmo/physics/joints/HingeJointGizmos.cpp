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
	return m_AnchorAHovered || m_AnchorBHovered;
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

	auto[modelMatrixA, positionA, angleA] = getBodyTransform(registry, bodyA);
	auto[modelMatrixB, positionB, angleB] = getBodyTransform(registry, hingeComponent.connectedBody);

	ImVec2 anchorA = getPoint(positionA, jointDef.localAnchorA, camera, modelMatrixA, angleA);
	ImVec2 anchorB = getPoint(positionB, jointDef.localAnchorB, camera, modelMatrixB, angleB);

	mouseHoversAnchors(anchorA, anchorB);

	updateAnchor(jointDef.localAnchorA, camera, modelMatrixA, positionA, angleA, m_AnchorAHovered);
	updateAnchor(jointDef.localAnchorB, camera, modelMatrixB, positionB, angleB, m_AnchorBHovered);

	drawAngleLimitsGizmo(anchorB, jointDef);
	drawAnchors(anchorA, anchorB);
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

std::tuple<glm::mat4, glm::vec3, float>
Survive::HingeJointGizmos::getBodyTransform(entt::registry &registry, entt::entity body)
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

void Survive::HingeJointGizmos::drawAnchors(const ImVec2 &anchorA, const ImVec2 &anchorB)
{
	drawAnchorConnector(anchorA, anchorB);

	drawAnchorA(anchorA);
	drawAnchorB(anchorB);
}

void Survive::HingeJointGizmos::updateAnchor(b2Vec2 &anchor, const Camera &camera, const glm::mat4 &modelMatrix,
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

void Survive::HingeJointGizmos::drawArc(float lowerAngle, float upperAngle, const ImVec2 &center)
{
	static constexpr ImU32 ARC_COLOR = IM_COL32(0, 255, 0, 60);

	float textHeight = ImGui::GetTextLineHeight();
	float radius = textHeight * 7.0f;

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	drawList->PathLineTo(center);
	drawList->PathArcTo(center, radius, lowerAngle, upperAngle);
	drawList->PathLineTo(center);
	drawList->PathFillConvex(ARC_COLOR);
}

void Survive::HingeJointGizmos::drawAngleLimitsGizmo(const ImVec2 &anchorB, const b2RevoluteJointDef &jointDef)
{
	if (jointDef.enableLimit)
	{
		drawArc(jointDef.lowerAngle, jointDef.upperAngle, anchorB);
	}
}
