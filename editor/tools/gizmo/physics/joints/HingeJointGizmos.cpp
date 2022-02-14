//
// Created by david on 24. 01. 2022..
//

#include "HingeJointGizmos.h"
#include "Util.h"

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

void Survive::HingeJointGizmos::drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera)
{
	HingeJoint2DComponent &hingeComponent = registry.get<HingeJoint2DComponent>(bodyA);
	b2RevoluteJointDef &jointDef = hingeComponent.jointDef;

	auto[modelMatrixA, positionA, angleA] = getBodyTransform(registry, bodyA);
	auto[modelMatrixB, positionB, angleB] = getBodyTransform(registry, hingeComponent.connectedBody);

	ImVec2 anchorA = getPoint(positionA, jointDef.localAnchorA, camera, modelMatrixA, angleA);
	ImVec2 anchorB = getPoint(positionB, jointDef.localAnchorB, camera, modelMatrixB, angleB);

	mouseHoversAnchors(anchorA, anchorB, m_AnchorAHovered, m_AnchorBHovered);

	updateAnchor(jointDef.localAnchorA, camera, modelMatrixA, positionA, angleA, m_AnchorAHovered);
	updateAnchor(jointDef.localAnchorB, camera, modelMatrixB, positionB, angleB, m_AnchorBHovered);

	drawAngleLimitsGizmo(anchorB, jointDef);
	drawAnchors(anchorA, anchorB, m_AnchorAHovered, m_AnchorBHovered);
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

bool Survive::HingeJointGizmos::isOver()
{
	return m_AnchorAHovered || m_AnchorBHovered;
}
