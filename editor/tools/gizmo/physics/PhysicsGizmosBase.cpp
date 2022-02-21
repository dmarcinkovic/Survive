//
// Created by david on 06. 11. 2021..
//

#include "PhysicsGizmosBase.h"
#include "Util.h"
#include "Constants.h"

void Survive::PhysicsGizmosBase::draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity)
{

}

void Survive::PhysicsGizmosBase::handleKeyEvents(const EventHandler &eventHandler)
{
	if (eventHandler.isKeyPressed(Key::A))
	{
		m_GizmoEnabled = true;
	} else if (eventHandler.isKeyPressed(Key::ESCAPE))
	{
		m_GizmoEnabled = false;
	}
}

void Survive::PhysicsGizmosBase::setRect(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

bool Survive::PhysicsGizmosBase::isEnabled() const
{
	return m_GizmoEnabled;
}

ImVec2
Survive::PhysicsGizmosBase::getPoint(const glm::vec3 &globalPos, const b2Vec2 &vertex, const Camera &camera,
									 const glm::mat4 &modelMatrix, float angle) const
{
	float scale = Constants::BOX2D_SCALE;

	glm::vec3 rotatedPoint = rotatePointAroundOrigin(vertex.x / scale, vertex.y / scale, angle);
	glm::vec3 point = globalPos + rotatedPoint;

	return Util::getScreenPos(camera, modelMatrix, point, m_X, m_Y, m_Width, m_Height);
}

glm::vec3 Survive::PhysicsGizmosBase::rotatePointAroundOrigin(float x, float y, float angle)
{
	float cosAngle = std::cos(angle);
	float sinAngle = std::sin(angle);

	return {x * cosAngle - y * sinAngle, y * cosAngle + x * sinAngle, 0};
}

void Survive::PhysicsGizmosBase::drawCenter(const ImVec2 &center, bool centerHovered)
{
	static constexpr ImU32 COLOR = IM_COL32(255, 255, 255, 255);
	static constexpr ImU32 COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	ImDrawList *drawList = ImGui::GetWindowDrawList();

	ImU32 color = centerHovered ? COLOR_HOVERED : COLOR;
	drawList->AddCircle(center, 4.0, color, 0, 2.0f);
}

ImVec2 Survive::PhysicsGizmosBase::getCenter(const b2Vec2 &localCenter, const Camera &camera, const glm::vec3 &position,
											 const glm::mat4 &modelMatrix, float x, float y, float width, float height)
{
	float scale = Constants::BOX2D_SCALE;
	glm::vec2 center{localCenter.x / scale, localCenter.y / scale};

	glm::vec2 point{center.x + position.x, center.y + position.y};

	return Util::getScreenPos(camera, modelMatrix, point, x, y, width, height);
}
