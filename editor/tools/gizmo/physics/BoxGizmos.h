//
// Created by david on 31. 10. 2021..
//

#ifndef SURVIVE_BOXGIZMOS_H
#define SURVIVE_BOXGIZMOS_H

#include <tuple>
#include <imgui.h>

#include "entt.hpp"
#include "Components.h"
#include "EventHandler.h"
#include "Camera.h"
#include "ColliderGizmos.h"

namespace Survive
{
	class BoxGizmos : public ColliderGizmos
	{
	private:
		static constexpr float RADIUS = 4.0f;

		static bool m_CenterHovered;
		static int m_HoveredLine;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

		static bool isOver();

	private:
		void drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
								  const Transform3DComponent &transform, const glm::mat4 &modelMatrix);

		static void initializeBoxCollider(BoxCollider2DComponent &boxCollider, const Transform3DComponent &transform);

		[[nodiscard]] std::tuple<ImVec2, ImVec2, ImVec2, ImVec2>
		getRectanglePoints(const BoxCollider2DComponent &boxCollider, const Transform3DComponent &transform,
						   const Camera &camera, const glm::mat4 &modelMatrix) const;

		static void drawRect(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, int hoveredLine);

		static void drawCenter(const ImVec2 &boxCenter, bool isHovered);

		[[nodiscard]] ImVec2 getBoxCenter(const BoxCollider2DComponent &boxCollider, const Camera &camera,
										  const Transform3DComponent &transform, const glm::mat4 &modelMatrix) const;

		static void drawLine(ImDrawList *drawList, const ImVec2 &p1, const ImVec2 &p2, bool isHovered);

		void drawHoveredLine(const Camera &camera, BoxCollider2DComponent &boxCollider, const glm::mat4 &modelMatrix,
							 float offset, int p1, int p2, bool isVertical) const;

		void drawHoveredPoint(const Camera &camera, BoxCollider2DComponent &boxCollider, const glm::mat4 &modelMatrix,
							  const glm::vec3 &position) const;

		void drawHoveredLines(const Camera &camera, BoxCollider2DComponent &boxCollider,
							  const Transform3DComponent &transform, const glm::mat4 &modelMatrix,
							  const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4);
	};
}

#endif //SURVIVE_BOXGIZMOS_H
