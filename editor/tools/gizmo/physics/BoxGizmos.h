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
#include "PolygonGizmos.h"

namespace Survive
{
	class BoxGizmos : public PolygonGizmos
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

		static void drawRect(const std::vector<ImVec2> &points, int hoveredLine);

		static void drawCenter(const ImVec2 &boxCenter, bool isHovered);

		[[nodiscard]] ImVec2 getBoxCenter(const BoxCollider2DComponent &boxCollider, const Camera &camera,
										  const Transform3DComponent &transform, const glm::mat4 &modelMatrix) const;

		static void drawLine(ImDrawList *drawList, const ImVec2 &p1, const ImVec2 &p2, bool isHovered);

		void drawHoveredLine(const Camera &camera, BoxCollider2DComponent &boxCollider, const glm::mat4 &modelMatrix,
							 float offset, int p1, int p2, bool isVertical) const;

		void drawHoveredPoint(const Camera &camera, BoxCollider2DComponent &boxCollider, const glm::mat4 &modelMatrix,
							  const glm::vec3 &position, float angle) const;

		void updateGizmos(const Camera &camera, BoxCollider2DComponent &boxCollider,
						  const Transform3DComponent &transform, const glm::mat4 &modelMatrix,
						  const std::vector<ImVec2> &points);
	};
}

#endif //SURVIVE_BOXGIZMOS_H
