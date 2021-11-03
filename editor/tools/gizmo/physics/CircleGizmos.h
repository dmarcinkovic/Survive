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
		bool m_Using{};

		static bool m_Hovered;

		float m_X{}, m_Y{}, m_Width{}, m_Height{};

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity);

		void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

		static bool isOver();

	private:
		[[nodiscard]] ImVec2 getCircleCenter(const CircleCollider2DComponent &circleCollider, const Camera &camera,
											 const Transform3DComponent &transform, const glm::mat4 &modelMatrix) const;

		[[nodiscard]] float calculateRadius(float radius, const Camera &camera, const glm::mat4 &modelMatrix) const;

		static bool mouseHoversCircle(const ImVec2 &center, float radius);

		static void initializeCircleCollider(CircleCollider2DComponent &circleCollider,
											 const Transform3DComponent &transform);

		void drawCircle(const ImVec2 &center, float radius) const;

		void updateCircleRadius(const ImVec2 &center, float radius, const Camera &camera, const glm::mat4 &modelMatrix,
								CircleCollider2DComponent &circleCollider) const;
	};
}

#endif //SURVIVE_CIRCLEGIZMOS_H
