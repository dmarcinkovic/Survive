//
// Created by david on 04. 11. 2021..
//

#ifndef SURVIVE_EDGEGIZMOS_H
#define SURVIVE_EDGEGIZMOS_H

#include "entt.hpp"
#include "Components.h"
#include "Camera.h"
#include "EventHandler.h"

namespace Survive
{
	class EdgeGizmos
	{
	private:
		bool isUsing{};

		float m_X{}, m_Y{}, m_Width{}, m_Height{};

		bool m_GizmoEnabled = true;

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity);

		void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

		static bool isOver();

	private:
		static void
		initializeEdgeCollider(EdgeCollider2DComponent &edgeCollider, const Transform3DComponent &transform);
	};
}

#endif //SURVIVE_EDGEGIZMOS_H
