//
// Created by david on 06. 11. 2021..
//

#ifndef SURVIVE_COLLIDERGIZMOS_H
#define SURVIVE_COLLIDERGIZMOS_H

#include <imgui.h>

#include "entt.hpp"
#include "Components.h"
#include "EventHandler.h"
#include "Camera.h"

namespace Survive
{
	class ColliderGizmos
	{
	protected:
		float m_X{}, m_Y{}, m_Width{}, m_Height{};

		bool m_GizmoEnabled{};

		bool m_IsUsing{};

	public:
		virtual void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity);

		void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

		[[nodiscard]] bool isEnabled() const;
	};
}

#endif //SURVIVE_COLLIDERGIZMOS_H
