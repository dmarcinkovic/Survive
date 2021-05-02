//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_ANIMATIONRENDERER_H
#define SURVIVE_ANIMATIONRENDERER_H

#include <unordered_map>
#include <functional>

#include "../../camera/Camera.h"
#include "../../light/Light.h"
#include "AnimationShader.h"
#include "../../objects/ObjectShader.h"
#include "../../../ecs/entt.hpp"
#include "../../core/texture/TexturedModel.h"

namespace Survive
{
	class AnimationRenderer
	{
	private:
		AnimationShader m_Shader;
		const Light &m_Light;

	public:
		explicit AnimationRenderer(const Light &light);

		void render(entt::registry &registry, const Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

	private:
		void renderScene(const entt::registry &registry, const std::vector<entt::entity> &objects,
						 const Camera &camera) const;

		static std::unordered_map<TexturedModel, std::vector<entt::entity>, TextureHash>
		prepareEntities(entt::registry &registry);

		void loadUniforms(const Camera &camera, const glm::vec4 &plane) const;
	};
}

#endif //SURVIVE_ANIMATIONRENDERER_H
