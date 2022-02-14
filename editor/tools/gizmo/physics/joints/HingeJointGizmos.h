//
// Created by david on 24. 01. 2022..
//

#ifndef SURVIVE_HINGEJOINTGIZMOS_H
#define SURVIVE_HINGEJOINTGIZMOS_H

#include <tuple>

#include "JointGizmos.h"

namespace Survive
{
	class HingeJointGizmos : public JointGizmos
	{
	private:
		static bool m_AnchorAHovered;
		static bool m_AnchorBHovered;

	public:
		static bool isOver();

	protected:
		void drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera) override;

	private:
		static void drawArc(float lowerAngle, float upperAngle, const ImVec2 &center);

		static void drawAngleLimitsGizmo(const ImVec2 &anchorB, const b2RevoluteJointDef &jointDef);
	};
}

#endif //SURVIVE_HINGEJOINTGIZMOS_H
