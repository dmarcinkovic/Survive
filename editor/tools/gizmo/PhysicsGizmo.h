//
// Created by david on 24. 10. 2021..
//

#ifndef SURVIVE_PHYSICSGIZMO_H
#define SURVIVE_PHYSICSGIZMO_H

#include "entt.hpp"
#include "BoxGizmos.h"
#include "EventHandler.h"
#include "Camera.h"

namespace Survive
{
	class PhysicsGizmo
	{
	private:
		BoxGizmos m_BoxGizmos;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity);

		void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

		static bool isOver();
	};
}

#endif //SURVIVE_PHYSICSGIZMO_H
