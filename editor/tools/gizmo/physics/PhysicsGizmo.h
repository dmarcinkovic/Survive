//
// Created by david on 24. 10. 2021..
//

#ifndef SURVIVE_PHYSICSGIZMO_H
#define SURVIVE_PHYSICSGIZMO_H

#include <entt.hpp>

#include "BoxGizmos.h"
#include "CircleGizmos.h"
#include "PolygonGizmos.h"
#include "EdgeGizmos.h"
#include "HingeJointGizmos.h"
#include "DistanceJointGizmos.h"
#include "EventHandler.h"
#include "Camera.h"

namespace Survive
{
	class PhysicsGizmo
	{
	private:
		BoxGizmos m_BoxGizmos;
		CircleGizmos m_CircleGizmos;
		EdgeGizmos m_EdgeGizmos;
		PolygonGizmos m_PolygonGizmos;

		HingeJointGizmos m_HingeGizmos;
		DistanceJointGizmos m_DistanceJointGizmos;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity);

		void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

		static bool isOver();

		[[nodiscard]] bool isEnabled() const;

	private:
		[[nodiscard]] bool isColliderGizmosEnabled() const;

		[[nodiscard]] bool isJointGizmosEnabled() const;
	};
}

#endif //SURVIVE_PHYSICSGIZMO_H
