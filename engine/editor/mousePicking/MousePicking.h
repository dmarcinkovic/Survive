//
// Created by david on 29. 12. 2020..
//

#ifndef SURVIVE_MOUSEPICKING_H
#define SURVIVE_MOUSEPICKING_H

#include <glm/glm.hpp>
#include <unordered_map>
#include <functional>

#include "entt.hpp"
#include "MousePickingShader.h"
#include "TexturedModel.h"
#include "Camera.h"

namespace Survive
{
	using MousePickingListener = std::function<void(int)>;

	class MousePicking
	{
	private:
		static bool mousePressed;
		static int selectedEntity;
		static bool listenerActive;

		MousePickingShader m_Shader;

		glm::vec2 m_MousePosition{};
		MousePickingListener m_Listener{};
		MousePickingListener m_ManagerListener{};

	public:
		explicit MousePicking();

		void render(entt::registry &registry, const Camera &camera) const;

		void setMousePosition(float mouseX, float mouseY);

		void addListener(const MousePickingListener &listener);

		void addManagerListener(const MousePickingListener &listener);

		static void removeListener();

	private:
		void mousePressedHandler();

		void renderScene(const entt::registry &registry,
						 const std::vector<entt::entity> &objects, const Camera &camera) const;

		void getRenderedObject() const;

		static glm::vec4 getColor(std::uint32_t id);

		static int getEntity(const std::uint8_t *data);

		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		void loadTransformationMatrix(const Camera &camera, const entt::registry &registry, entt::entity entity) const;

		[[nodiscard]] bool isInsideWindow() const;

		static void setViewport();

		void prepareRendering(const Camera &camera) const;

		void informListener(int entity) const;
	};
}

#endif //SURVIVE_MOUSEPICKING_H
