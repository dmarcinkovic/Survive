//
// Created by david on 31. 10. 2021..
//

#ifndef SURVIVE_BOXGIZMOS_H
#define SURVIVE_BOXGIZMOS_H

#include <imgui.h>

#include "entt.hpp"
#include "Components.h"
#include "EventHandler.h"
#include "Camera.h"
#include "PolygonGizmos.h"
#include "Centroid.h"

namespace Survive
{
	class BoxGizmos : public PolygonGizmos, public Centroid
	{
	private:
		static constexpr float RADIUS = 4.0f;

		static int m_HoveredLine;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

		static bool isOver();

	private:
		void drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
								  const Transform3DComponent &transform);

		static void initializeBoxCollider(BoxCollider2DComponent &boxCollider, const Transform3DComponent &transform);

		static void drawRect(const std::vector<ImVec2> &points, int hoveredLine);

		static void drawLine(ImDrawList *drawList, const ImVec2 &p1, const ImVec2 &p2, bool isHovered);

		void moveLine(const Camera &camera, BoxCollider2DComponent &boxCollider, const glm::mat4 &modelMatrix,
					  const glm::vec3 &position, float angle, int p1, int p2, bool isVertical) const;

		void moveCenter(const Camera &camera, BoxCollider2DComponent &boxCollider, const glm::mat4 &modelMatrix,
						const glm::vec3 &position, float angle) const;

		void updateGizmos(const Camera &camera, BoxCollider2DComponent &boxCollider,
						  const Transform3DComponent &transform, const glm::mat4 &modelMatrix,
						  const std::vector<ImVec2> &points, const ImVec2 &center);

		void updateLines(const Camera &camera, BoxCollider2DComponent &boxCollider,
						 const Transform3DComponent &transform, const glm::mat4 &modelMatrix,
						 const std::vector<ImVec2> &points);

		void updateCenter(const ImVec2 &center, const Camera &camera, BoxCollider2DComponent &boxCollider,
						  const Transform3DComponent &transform, const glm::mat4 &modelMatrix);

		[[nodiscard]] ImVec2 calcCenter(const b2Vec2 &localCenter, const Camera &camera, const glm::vec3 &position,
										const glm::mat4 &modelMatrix, float angle) const;

		void mouseHoversLine(const std::vector<ImVec2> &points);

		void moveLines(const Camera &camera, BoxCollider2DComponent &boxCollider,
					   const Transform3DComponent &transform, const glm::mat4 &modelMatrix);
	};
}

#endif //SURVIVE_BOXGIZMOS_H
