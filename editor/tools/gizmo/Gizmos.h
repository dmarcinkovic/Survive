//
// Created by david on 05. 08. 2021..
//

#ifndef SURVIVE_GIZMOS_H
#define SURVIVE_GIZMOS_H

#include <imgui.h>
#include <ImGuizmo.h>

#include "entt.hpp"
#include "Camera.h"
#include "EventHandler.h"
#include "Transform3DComponent.h"

namespace Survive
{
	class Gizmos
	{
	private:
		float m_X{}, m_Y{}, m_Width{}, m_Height{};

		ImGuizmo::OPERATION m_Operation{};
		bool m_DrawGizmos{};

	public:
		Gizmos();

		void draw(entt::registry &registry, const Camera &camera, entt::entity selectedEntity) const;

		static void newFrame();

		void setRect(float x, float y, float width, float height);

		void handleKeyEvents(const EventHandler &eventHandler);

	private:
		static glm::mat4 getTransform(const Transform3DComponent &transform);

		static void useGizmo(Transform3DComponent &transformComponent, glm::mat4 &transform);
	};
}

#endif //SURVIVE_GIZMOS_H
