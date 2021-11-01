//
// Created by david on 01. 11. 2021..
//

#ifndef SURVIVE_CIRCLEGIZMOS_H
#define SURVIVE_CIRCLEGIZMOS_H

#include "entt.hpp"
#include "Camera.h"
#include "EventHandler.h"
#include "CircleCollider2DComponent.h"

namespace Survive
{
	class CircleGizmos
	{
	private:
		bool m_GizmoEnabled = true;

		float m_X{}, m_Y{}, m_Width{}, m_Height{};

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity);

		void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

		static bool isOver();

	private:
		ImVec2 getCircleCenter(const CircleCollider2DComponent &circleCollider, const Camera &camera,
							   const Transform3DComponent &transform, const glm::mat4 &modelMatrix) const;

		float calculateRadius(float radius, const Camera &camera, const glm::mat4 &modelMatrix);
	};
}

#endif //SURVIVE_CIRCLEGIZMOS_H
