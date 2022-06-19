//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_ANIMATIONRENDERER_H
#define SURVIVE_ANIMATIONRENDERER_H

#include <unordered_map>
#include <functional>
#include <entt.hpp>

#include "Joint.h"
#include "AnimationShader.h"
#include "TexturedModel.h"
#include "ObjectRenderer.h"
#include "Components.h"
#include "Camera.h"
#include "Light.h"

namespace Survive
{
	class AnimationRenderer : public ObjectRenderer
	{
	private:
		AnimationShader m_Shader;

	public:
		explicit AnimationRenderer(const Light &light);

		void renderAnimation(entt::registry &registry, const Camera &camera, GLuint shadowMap,
							 const glm::vec4 &plane = glm::vec4{}) const;

	private:
		void renderScene(entt::registry &registry, const std::vector<entt::entity> &objects,
						 const Camera &camera) const;

		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		void loadUniforms(const Camera &camera, GLuint shadowMap, const glm::vec4 &plane) const;

		void loadObjectUniforms(entt::registry &registry, entt::entity entity,
								const Texture &texture, const Camera &camera) const;
	};
}

#endif //SURVIVE_ANIMATIONRENDERER_H
