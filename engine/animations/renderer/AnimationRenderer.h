//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_ANIMATIONRENDERER_H
#define SURVIVE_ANIMATIONRENDERER_H

#include <unordered_map>
#include <functional>

#include "entt.hpp"
#include "Joint.h"
#include "AnimationShader.h"
#include "TexturedModel.h"
#include "Components.h"
#include "Camera.h"
#include "Light.h"

namespace Survive
{
	class AnimationRenderer
	{
	private:
		AnimationShader m_Shader;
		const Light &m_Light;

	public:
		explicit AnimationRenderer(const Light &light);

		void render(entt::registry &registry, const Camera &camera, GLuint shadowMap,
					const glm::vec4 &plane = glm::vec4{}) const;

	private:
		void renderScene(const entt::registry &registry, const std::vector<entt::entity> &objects,
						 const Camera &camera) const;

		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		void loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const;

		void loadObjectUniforms(const entt::registry &registry, entt::entity entity,
								const Texture &texture, const Camera &camera) const;

		void renderBloom(const entt::registry &registry, entt::entity entity) const;

		void renderReflectionAndRefraction(const entt::registry &registry, entt::entity entity) const;

		static void drawOutline(const entt::registry &registry, entt::entity entity);

		void loadMaterial(const entt::registry &registry, entt::entity entity) const;
	};
}

#endif //SURVIVE_ANIMATIONRENDERER_H
