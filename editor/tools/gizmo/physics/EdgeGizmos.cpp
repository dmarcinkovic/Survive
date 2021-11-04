//
// Created by david on 04. 11. 2021..
//

#include <imgui.h>

#include "EdgeGizmos.h"
#include "Maths.h"
#include "Constants.h"
#include "Util.h"

void Survive::EdgeGizmos::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{
	if (selectedEntity != entt::null &&
		registry.all_of<EdgeCollider2DComponent, Transform3DComponent, Render2DComponent>(selectedEntity))
	{
		EdgeCollider2DComponent &edgeCollider = registry.get<EdgeCollider2DComponent>(selectedEntity);
		const Transform3DComponent &transform = registry.get<Transform3DComponent>(selectedEntity);

		initializeEdgeCollider(edgeCollider, transform);

		if (m_GizmoEnabled)
		{
			glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position);

			ImVec2 p1 = getPoint(transform.position, edgeCollider.edgeShape.m_vertex1, camera, modelMatrix);
			ImVec2 p2 = getPoint(transform.position, edgeCollider.edgeShape.m_vertex2, camera, modelMatrix);

			ImDrawList *drawList = ImGui::GetWindowDrawList();
			drawList->AddLine(p1, p2, IM_COL32(255, 255, 255, 255), 3.0f);
			drawList->AddCircleFilled(p1, 5, IM_COL32(0, 0, 255, 255));
			drawList->AddCircleFilled(p2, 5, IM_COL32(0, 0, 255, 255));
		}
	}
}

void Survive::EdgeGizmos::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::A))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
}

void Survive::EdgeGizmos::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

bool Survive::EdgeGizmos::isOver()
{
	return false;
}

void Survive::EdgeGizmos::initializeEdgeCollider(EdgeCollider2DComponent &edgeCollider,
												 const Transform3DComponent &transform)
{
	if (!edgeCollider.m_Initialized)
	{
		glm::vec3 scale = transform.scale * Constants::BOX2D_SCALE;

		edgeCollider.edgeShape.m_vertex1 = b2Vec2(-scale.x, scale.y);
		edgeCollider.edgeShape.m_vertex2 = b2Vec2(scale.x, scale.y);

		edgeCollider.m_Initialized = true;
	}
}

ImVec2 Survive::EdgeGizmos::getPoint(const glm::vec3 &globalPos, const b2Vec2 &vertex, const Camera &camera,
									 const glm::mat4 &modelMatrix) const
{
	float scale = Constants::BOX2D_SCALE;

	glm::vec3 point = globalPos + glm::vec3{vertex.x / scale, vertex.y / scale, 0};
	return Util::getScreenPos(camera, modelMatrix, point, m_X, m_Y, m_Width, m_Height);
}
