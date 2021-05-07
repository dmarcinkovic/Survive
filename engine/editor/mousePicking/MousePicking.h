//
// Created by david on 29. 12. 2020..
//

#ifndef SURVIVE_MOUSEPICKING_H
#define SURVIVE_MOUSEPICKING_H

#include <glm/glm.hpp>
#include <unordered_map>
#include <functional>

#include "MousePickingShader.h"
#include "entt.hpp"
#include "TexturedModel.h"
#include "Camera.h"

namespace Survive
{
	class MousePicking
	{
	private:
		static bool mousePressed;
		MousePickingShader m_Shader;

		glm::ivec2 m_MousePosition{};

	public:
		explicit MousePicking();

		void render(entt::registry &registry, const Camera &camera) const;

	private:
		void mousePressedHandler();

		void renderScene(const entt::registry &registry,
						 const std::vector<entt::entity> &objects, const Camera &camera) const;

		void getRenderedObject() const;

		static glm::vec4 getColor(std::uint32_t id);

		static int getID(const std::uint8_t *data);

		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		void loadTransformationMatrix(const Camera &camera, const entt::registry &registry, entt::entity entity) const;
	};
}

#endif //SURVIVE_MOUSEPICKING_H
