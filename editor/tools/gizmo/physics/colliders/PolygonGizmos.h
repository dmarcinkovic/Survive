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
#include "PhysicsGizmosBase.h"

namespace Survive
{
	class PolygonGizmos : public PhysicsGizmosBase
	{
	private:
		static int m_PointHovered;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

		static bool isOver();

	protected:
		void moveVertex(const Camera &camera, const glm::mat4 &modelMatrix,
						const glm::vec3 &position, b2Vec2 &vertex, float angle) const;

		std::vector<ImVec2> getPolygonPoints(const std::vector<b2Vec2> &points, const glm::vec3 &globalPos,
											 const Camera &camera, const glm::mat4 &modelMatrix, float angle);

		[[nodiscard]] glm::vec3
		getMouseLocalPosition(const Camera &camera, const glm::mat4 &modelMatrix, const glm::vec3 &position) const;

	private:
		static void drawPoints(const std::vector<ImVec2> &points);

		static void drawLines(const std::vector<ImVec2> &points);

		static void drawGizmos(const std::vector<ImVec2> &polygonPoints);

		void updateGizmo(const Camera &camera, const glm::mat4 &modelMatrix, const glm::vec3 &position,
						 const std::vector<ImVec2> &polygonPoints, std::vector<b2Vec2> &points,
						 b2PolygonShape &shape, float angle);

		void enableGizmos(PolygonCollider2DComponent &polygonCollider, const Transform3DComponent &transform,
						  const Camera &camera);
	};
}


#endif //SURVIVE_POLYGONGIZMOS_H
