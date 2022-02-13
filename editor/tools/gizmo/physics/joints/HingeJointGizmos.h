//
// Created by david on 24. 01. 2022..
//

#ifndef SURVIVE_HINGEJOINTGIZMOS_H
#define SURVIVE_HINGEJOINTGIZMOS_H

#include "PhysicsGizmosBase.h"
#include "Components.h"

namespace Survive
{
	class HingeJointGizmos : public PhysicsGizmosBase
	{
	private:
		static constexpr float ANCHOR_RADIUS = 7.0f;
		static constexpr ImU32 ANCHOR_COLOR = IM_COL32(0, 0, 230, 255);
		static constexpr ImU32 ANCHOR_CONNECTOR_COLOR = IM_COL32(0, 255, 0, 255);
		static constexpr ImU32 CIRCLE_COLOR_HOVERED = IM_COL32(255, 90, 0, 255);

		static bool m_AnchorAHovered;
		static bool m_AnchorBHovered;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

		static bool isOver();

		void handleKeyEvents(const EventHandler &eventHandler) override;

	private:
		void drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera);

		static void drawAnchorA(const ImVec2 &anchorPosition);

		static void drawAnchorB(const ImVec2 &anchorPosition);

		static void drawAnchorConnector(const ImVec2 &anchorA, const ImVec2 &anchorB);

		ImVec2
		getAnchorPosition(entt::registry &registry, entt::entity body, const Camera &camera, const b2Vec2 &anchor);

		void mouseHoversAnchors(const ImVec2 &anchorA, const ImVec2 &anchorB);
	};
}

#endif //SURVIVE_HINGEJOINTGIZMOS_H
