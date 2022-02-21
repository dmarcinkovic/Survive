//
// Created by david on 06. 11. 2021..
//

#ifndef SURVIVE_PHYSICSGIZMOSBASE_H
#define SURVIVE_PHYSICSGIZMOSBASE_H

#include <imgui.h>

#include "entt.hpp"
#include "Components.h"
#include "EventHandler.h"
#include "Camera.h"

namespace Survive
{
	class PhysicsGizmosBase
	{
	protected:
		float m_X{}, m_Y{}, m_Width{}, m_Height{};

		bool m_GizmoEnabled{};

		bool m_IsUsing{};

	public:
		virtual void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity);

		virtual void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

		[[nodiscard]] bool isEnabled() const;

	protected:
		ImVec2 getPoint(const glm::vec3 &globalPos, const b2Vec2 &vertex, const Camera &camera,
						const glm::mat4 &modelMatrix, float angle) const;

		static glm::vec3 rotatePointAroundOrigin(float x, float y, float angle);

		static void drawCenter(const ImVec2 &center, bool centerHovered);

		static ImVec2 getCenter(const b2Vec2 &localCenter, const Camera &camera, const glm::vec3 &position,
								const glm::mat4 &modelMatrix, float x, float y, float width, float height);
	};
}

#endif //SURVIVE_PHYSICSGIZMOSBASE_H
