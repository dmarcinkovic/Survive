//
// Created by david on 28. 11. 2021..
//

#ifndef SURVIVE_POLYGONGIZMOS_H
#define SURVIVE_POLYGONGIZMOS_H

#include <vector>

#include "entt.hpp"
#include "Components.h"
#include "Camera.h"
#include "EventHandler.h"
#include "ColliderGizmos.h"

namespace Survive
{
	class PolygonGizmos : public ColliderGizmos
	{
	private:
		static int m_PointHovered;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

		static bool isOver();

	private:
		[[nodiscard]] ImVec2 getPoint(const glm::vec3 &globalPos, const b2Vec2 &vertex, const Camera &camera,
									  const glm::mat4 &modelMatrix) const;

		std::vector<ImVec2> getPolygonPoints(const std::vector<b2Vec2> &points, const glm::vec3 &globalPos,
											 const Camera &camera, const glm::mat4 &modelMatrix);

		static void drawPoints(const std::vector<ImVec2> &points);

		static void drawLines(const std::vector<ImVec2> &points);

		static void drawGizmos(const std::vector<ImVec2> &polygonPoints);

		void updateGizmo(const Camera &camera, const glm::mat4 &modelMatrix, const glm::vec3 &position,
						 const std::vector<ImVec2> &points);
	};
}


#endif //SURVIVE_POLYGONGIZMOS_H
