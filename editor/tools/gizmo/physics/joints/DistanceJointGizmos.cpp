//
// Created by david on 14. 02. 2022..
//

#include "DistanceJointGizmos.h"
#include "Util.h"
#include "Constants.h"

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

	drawLengthLimits(camera, anchorA, anchorB, jointDef.minLength, jointDef.maxLength);
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
	} else
	{
		m_GizmoEnabled = false;
	}
}

void Survive::DistanceJointGizmos::drawLengthLimits(const Camera &camera, const ImVec2 &anchorA, const ImVec2 &anchorB,
													float minLength, float maxLength)
{
	float meterInScreenSpace = meterToPixelUnit(camera);

	glm::vec2 direction{anchorA.x - anchorB.x, anchorA.y - anchorB.y};
	direction = glm::normalize(direction);

	glm::vec2 perpendicular = getPerpendicularVector(direction);

	direction *= meterInScreenSpace;

	glm::vec2 minLimit = glm::vec2{anchorB.x, anchorB.y} + direction * minLength;
	glm::vec2 maxLimit = glm::vec2{anchorB.x, anchorB.y} + direction * maxLength;

	drawPerpendicularVector(minLimit, perpendicular);
	drawPerpendicularVector(maxLimit, perpendicular);
	extendAnchorConnector(anchorA, ImVec2{maxLimit.x, maxLimit.y});
}

float Survive::DistanceJointGizmos::meterToPixelUnit(const Camera &camera)
{
	constexpr float scale = Constants::BOX2D_SCALE;
	constexpr float unitLength = 1.0f / scale;

	constexpr glm::vec2 unitVector{unitLength, 0.0f};
	constexpr glm::mat4 transformationMatrix{1.0f};

	ImVec2 unit = Util::getScreenPos(camera, transformationMatrix, unitVector, m_X, m_Y, m_Width, m_Height);
	ImVec2 origin = Util::getScreenPos(camera, transformationMatrix, {0.0f, 0.0f}, m_X, m_Y, m_Width, m_Height);

	return unit.x - origin.x;
}

glm::vec2 Survive::DistanceJointGizmos::getPerpendicularVector(const glm::vec2 &vector)
{
	return {vector.y, -vector.x};
}

void Survive::DistanceJointGizmos::drawPerpendicularVector(const glm::vec2 &point, const glm::vec2 &perpendicular)
{
	static constexpr ImU32 LINE_COLOR = IM_COL32(0, 255, 0, 255);

	float size = ImGui::GetTextLineHeight();
	glm::vec2 scaled = perpendicular * size;

	ImVec2 p1{point.x + scaled.x, point.y + scaled.y};
	ImVec2 p2{point.x - scaled.x, point.y - scaled.y};

	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddLine(p1, p2, LINE_COLOR, 2.0f);
}

void Survive::DistanceJointGizmos::extendAnchorConnector(const ImVec2 &anchorA, const ImVec2 &maxLimit)
{
	static constexpr ImU32 CONNECTOR_COLOR = IM_COL32(0, 255, 0, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddLine(anchorA, maxLimit, CONNECTOR_COLOR);
}
