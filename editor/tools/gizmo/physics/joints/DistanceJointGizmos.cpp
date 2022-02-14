//
// Created by david on 14. 02. 2022..
//

#include "DistanceJointGizmos.h"

bool Survive::DistanceJointGizmos::m_AnchorAHovered{};
bool Survive::DistanceJointGizmos::m_AnchorBHovered{};

bool Survive::DistanceJointGizmos::isOver()
{
	return m_AnchorAHovered || m_AnchorBHovered;
}

void Survive::DistanceJointGizmos::drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera)
{
	DistanceJoint2DComponent &distanceJoint = registry.get<DistanceJoint2DComponent>(bodyA);
	b2DistanceJointDef &jointDef = distanceJoint.jointDef;

	auto[modelMatrixA, positionA, angleA] = getBodyTransform(registry, bodyA);
	auto[modelMatrixB, positionB, angleB] = getBodyTransform(registry, distanceJoint.connectedBody);

	ImVec2 anchorA = getPoint(positionA, jointDef.localAnchorA, camera, modelMatrixA, angleA);
	ImVec2 anchorB = getPoint(positionB, jointDef.localAnchorB, camera, modelMatrixB, angleB);

	mouseHoversAnchors(anchorA, anchorB, m_AnchorAHovered, m_AnchorBHovered);

	updateAnchor(jointDef.localAnchorA, camera, modelMatrixA, positionA, angleA, m_AnchorAHovered);
	updateAnchor(jointDef.localAnchorB, camera, modelMatrixB, positionB, angleB, m_AnchorBHovered);

	drawAnchors(anchorA, anchorB, m_AnchorAHovered, m_AnchorBHovered);
}

void Survive::DistanceJointGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity == entt::null)
	{
		m_GizmoEnabled = false;
	}

	if (selectedEntity != entt::null && registry.all_of<DistanceJoint2DComponent, Transform3DComponent>(selectedEntity))
	{
		if (m_GizmoEnabled)
		{
			m_IsUsing = ImGui::IsMouseDragging(ImGuiMouseButton_Left);

			drawGizmos(registry, selectedEntity, camera);
		}
	}
}
