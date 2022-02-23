//
// Created by david on 14. 02. 2022..
//

#ifndef SURVIVE_JOINTGIZMOS_H
#define SURVIVE_JOINTGIZMOS_H

#include <tuple>

#include "PhysicsGizmosBase.h"
#include "Components.h"

namespace Survive
{
	class JointGizmos : public PhysicsGizmosBase
	{
	private:
		static constexpr float ANCHOR_RADIUS = 7.0f;

		static constexpr ImU32 ANCHOR_COLOR = IM_COL32(0, 0, 230, 255);
		static constexpr ImU32 ANCHOR_CONNECTOR_COLOR = IM_COL32(0, 255, 0, 255);
		static constexpr ImU32 CIRCLE_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

	public:
		void handleKeyEvents(const EventHandler &eventHandler) override;

	protected:
		virtual void drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera);

		void mouseHoversAnchors(const ImVec2 &anchorA, const ImVec2 &anchorB,
								bool &anchorAHovered, bool &anchorBHovered);

		static std::tuple<glm::mat4, glm::vec3, float> getBodyTransform(entt::registry &registry, entt::entity body);

		void updateAnchor(b2Vec2 &anchor, const Camera &camera, const glm::mat4 &modelMatrix,
						  const glm::vec3 &position, float angle, bool isHovered) const;

		static void drawAnchors(const ImVec2 &anchorA, const ImVec2 &anchorB, bool anchorAHovered, bool anchorBHovered);

	private:
		static void drawAnchorA(const ImVec2 &anchorPosition, bool isAnchorHovered);

		static void drawAnchorB(const ImVec2 &anchorPosition, bool isAnchorHovered);

		static void drawAnchorConnector(const ImVec2 &anchorA, const ImVec2 &anchorB);
	};
}

#endif //SURVIVE_JOINTGIZMOS_H
