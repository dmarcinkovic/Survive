//
// Created by david on 24. 01. 2022..
//

#include "HingeJointGizmos.h"
#include "Maths.h"
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

	ImVec2 anchorA = getAnchorPosition(registry, bodyA, camera, jointDef.localAnchorA);
	ImVec2 anchorB = getAnchorPosition(registry, hingeComponent.connectedBody, camera, jointDef.localAnchorB);

	drawAnchorA(anchorA);
	drawAnchorB(anchorB);
}

void Survive::HingeJointGizmos::drawAnchorA(const ImVec2 &anchorPosition)
{
	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddCircle(anchorPosition, ANCHOR_RADIUS, ANCHOR_COLOR, 0, 3.0f);
}

void Survive::HingeJointGizmos::drawAnchorB(const ImVec2 &anchorPosition)
{
	ImDrawList *drawList = ImGui::GetWindowDrawList();
	drawList->AddCircleFilled(anchorPosition, ANCHOR_RADIUS, ANCHOR_COLOR);
}

ImVec2 Survive::HingeJointGizmos::getAnchorPosition(entt::registry &registry, entt::entity body, const Camera &camera,
													const b2Vec2 &anchor)
{
	if (body != entt::null)
	{
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(body);
		glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

		float angle = glm::radians(transform.rotation.z);

		return getPoint(transform.position, anchor, camera, modelMatrix, angle);
	}

	return getPoint(glm::vec3{0.0f}, anchor, camera, glm::mat4{1.0f}, 0.0f);
}
