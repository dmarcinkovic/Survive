//
// Created by david on 24. 10. 2021..
//

#ifndef SURVIVE_PHYSICSGIZMO_H
#define SURVIVE_PHYSICSGIZMO_H

#include "entt.hpp"
#include "Components.h"
#include "EventHandler.h"
#include "Camera.h"

namespace Survive
{
	class PhysicsGizmo
	{
	private:
		float m_X{}, m_Y{}, m_Width{}, m_Height{};

	public:
		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) const;

		void handleKeyEvents(const EventHandler &eventHandler);

		void setRect(float x, float y, float width, float height);

	private:
		[[nodiscard]] glm::vec2 getScreenPos(const Camera &camera, const glm::mat4 &transformationMatrix,
											 const glm::vec3 &point) const;

		void drawBoxColliderGizmo(const Camera &camera, BoxCollider2DComponent &boxCollider,
								  const Transform3DComponent &transform, const glm::mat4 &modelMatrix) const;
	};
}

#endif //SURVIVE_PHYSICSGIZMO_H
