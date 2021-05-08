//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECTRENDERER_H
#define SURVIVE_OBJECTRENDERER_H

#include <unordered_map>
#include <functional>

#include "entt.hpp"
#include "ObjectShader.h"
#include "Camera.h"
#include "Light.h"
#include "TexturedModel.h"

namespace Survive
{
	class ObjectRenderer
	{
	private:
		ObjectShader m_Shader;
		const Light &m_Light;

	public:
		explicit ObjectRenderer(const Light &light);

		void render(entt::registry &registry, const Camera &camera, GLuint shadowMap,
					const glm::vec4 &plane = glm::vec4{}) const;

	private:
		void
		renderScene(const entt::registry &registry, const std::vector<entt::entity> &objects,
					const Camera &camera) const;

		void loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const;

		void loadObjectUniforms(const entt::registry &registry, entt::entity, const Camera &camera) const;

		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		static void drawOutline(const entt::registry &registry, entt::entity entity);

		void renderBloom(const entt::registry &registry, entt::entity entity) const;

		void renderReflectionAndRefraction(const entt::registry &registry, entt::entity entity) const;
	};
}

#endif //SURVIVE_OBJECTRENDERER_H
