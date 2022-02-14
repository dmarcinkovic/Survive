//
// Created by david on 14. 02. 2022..
//

#ifndef SURVIVE_DISTANCEJOINTGIZMOS_H
#define SURVIVE_DISTANCEJOINTGIZMOS_H

#include "JointGizmos.h"

namespace Survive
{
	class DistanceJointGizmos : public JointGizmos
	{
	private:
		static bool m_AnchorAHovered;
		static bool m_AnchorBHovered;

	public:
		static bool isOver();

		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) override;

	protected:
		void drawGizmos(entt::registry &registry, entt::entity bodyA, const Camera &camera) override;

	};
}

#endif //SURVIVE_DISTANCEJOINTGIZMOS_H
