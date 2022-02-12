//
// Created by david on 24. 01. 2022..
//

#include <iostream>

#include "HingeJointGizmos.h"
#include "Maths.h"
#include "Constants.h"
#include "Util.h"

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
	return false;
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
	const b2RevoluteJointDef &jointDef = hingeComponent.jointDef;

	drawAnchorA(registry, bodyA, camera, jointDef.localAnchorA);
	drawAnchorB(registry, hingeComponent.connectedBody, camera, jointDef.localAnchorB);
}

void Survive::HingeJointGizmos::drawAnchorA(entt::registry &registry, entt::entity bodyA, const Camera &camera,
											const b2Vec2 &anchor)
{
	ImVec2 anchorPosition = getAnchorPosition(registry, bodyA, camera, anchor);

	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddCircle(anchorPosition, 7, IM_COL32(0, 0, 230, 255), 0, 3.0f);
}

void Survive::HingeJointGizmos::drawAnchorB(entt::registry &registry, entt::entity bodyB, const Camera &camera,
											const b2Vec2 &anchor)
{
	ImVec2 anchorPosition;

	if (bodyB == entt::null)
	{
		anchorPosition = getPoint(glm::vec3{0.0f}, anchor, camera, glm::mat4{1.0f}, 0.0f);
	} else
	{
		anchorPosition = getAnchorPosition(registry, bodyB, camera, anchor);
	}

	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddCircleFilled(anchorPosition, 5, IM_COL32(0, 0, 200, 255));
}

ImVec2 Survive::HingeJointGizmos::getAnchorPosition(entt::registry &registry, entt::entity body, const Camera &camera,
													const b2Vec2 &anchor)
{
	const Transform3DComponent &transform = registry.get<Transform3DComponent>(body);
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

	float angle = glm::radians(transform.rotation.z);

	return getPoint(transform.position, anchor, camera, modelMatrix, angle);
}
