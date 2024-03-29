//
// Created by david on 04. 11. 2021..
//

#ifndef SURVIVE_EDGEGIZMOS_H
#define SURVIVE_EDGEGIZMOS_H

#include <entt.hpp>

#include "Components.h"
#include "Camera.h"
#include "EventHandler.h"
#include "PolygonGizmos.h"

namespace Survive
{
	class EdgeGizmos : public PolygonGizmos
	{
	private:
		static constexpr float RADIUS = 5.0f;

		static int m_PointHovered;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

		static bool isOver();

	private:
		static void
		initializeEdgeCollider(EdgeCollider2DComponent &edgeCollider, const Transform3DComponent &transform);

		static void drawGizmo(const ImVec2 &p1, const ImVec2 &p2);

		void updateGizmo(const Camera &camera, const glm::mat4 &modelMatrix, const glm::vec3 &position,
						 EdgeCollider2DComponent &edgeCollider, const ImVec2 &p1, const ImVec2 &p2, float angle);

		void enableGizmos(EdgeCollider2DComponent &edgeCollider, const Transform3DComponent &transform,
						  const Camera &camera);
	};
}

#endif //SURVIVE_EDGEGIZMOS_H
