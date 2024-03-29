//
// Created by david on 05. 08. 2021..
//

#ifndef SURVIVE_GIZMOS_H
#define SURVIVE_GIZMOS_H

#include <imgui.h>
#include <ImGuizmo.h>
#include <entt.hpp>

#include "Camera.h"
#include "EventHandler.h"
#include "Transform3DComponent.h"
#include "PhysicsGizmo.h"

namespace Survive
{
	class Gizmos
	{
	private:
		static bool m_ValidOperation;

		float m_X{}, m_Y{}, m_Width{}, m_Height{};
		ImGuizmo::OPERATION m_Operation{};

		PhysicsGizmo m_Gizmos;

	public:
		void draw(entt::registry &registry, Camera &camera, entt::entity selectedEntity);

		static void newFrame();

		void setRect(float x, float y, float width, float height);

		void handleKeyEvents(const EventHandler &eventHandler);

		static bool isValidOperation();

		static bool isInsideViewGizmo();

	private:
		static glm::mat4 getTransform(const Transform3DComponent &transform);

		static void useGizmo(Transform3DComponent &transformComponent, glm::mat4 &transform);

		void drawGizmos(bool isOrthographic, const glm::mat4 &projectionMatrix, const glm::mat4 &viewMatrix,
						entt::registry &registry, entt::entity entity) const;

		void drawViewGizmos(Camera &camera) const;

		static void decomposeViewMatrix(Camera &camera, const glm::mat4 &viewMatrix);

		static std::pair<ImVec2, ImVec2> getViewGizmoRect();

		static bool viewMatrixChanged(const glm::mat4 &oldViewMatrix, const glm::mat4 &newViewMatrix);
	};
}

#endif //SURVIVE_GIZMOS_H
