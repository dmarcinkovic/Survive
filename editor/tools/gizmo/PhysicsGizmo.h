//
// Created by david on 24. 10. 2021..
//

#ifndef SURVIVE_PHYSICSGIZMO_H
#define SURVIVE_PHYSICSGIZMO_H

#include "entt.hpp"
#include "Components.h"
#include "EventHandler.h"
#include "Camera.h"

namespace Survive
{
	class PhysicsGizmo
	{
	private:
		float m_X{}, m_Y{}, m_Width{}, m_Height{};

		const ImU32 lineColor = IM_COL32(255, 255, 255, 255);
		const ImU32 lineColorHovered = IM_COL32(255, 90, 0, 255);

		mutable bool m_Using{};

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) const;

		void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

		bool isUsing() const;

	private:
		[[nodiscard]] ImVec2 getScreenPos(const Camera &camera, const glm::mat4 &transformationMatrix,
										  const glm::vec3 &point) const;

		glm::vec3 getLocalSpace(const Camera &camera, const glm::mat4 &transformationMatrix, const ImVec2 &point) const;

		void drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
								  const Transform3DComponent &transform, const glm::mat4 &modelMatrix) const;

		static void initializeBoxCollider(BoxCollider2DComponent &boxCollider, const Transform3DComponent &transform);

		[[nodiscard]] std::tuple<ImVec2, ImVec2, ImVec2, ImVec2>
		getRectanglePoints(const BoxCollider2DComponent &boxCollider, const Transform3DComponent &transform,
						   const Camera &camera, const glm::mat4 &modelMatrix) const;

		static void drawRect(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 rectColor,
							 ImU32 circleColor);

		static glm::vec2 getBoxCenter(const BoxCollider2DComponent &boxCollider, const Transform3DComponent &transform);

		static bool mouseHoversLine(const ImVec2 &p1, const ImVec2 &p2);

		static float lineDistance(const ImVec2 &p1, const ImVec2 &p2);
	};
}

#endif //SURVIVE_PHYSICSGIZMO_H
