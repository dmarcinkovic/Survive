//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAINRENDERER_H
#define SURVIVE_TERRAINRENDERER_H

#include "entt.hpp"
#include "TerrainShader.h"
#include "Components.h"
#include "Camera.h"

namespace Survive
{
	class TerrainRenderer
	{
	private:
		TerrainShader m_Shader;

	public:
		void render(entt::registry &registry, const Camera &camera, const Light &light, GLuint shadowMap,
					const glm::vec4 &plane = glm::vec4{}) const;

	private:
		static void prepareRendering(const Render3DComponent &renderComponent, const TexturedComponent &textures);

		static void finishRendering();

		void renderShadow(GLuint shadowMap, const Light &light) const;

		void loadUniforms(const Camera &camera, const Light &light, const glm::vec4 &plane,
						  const Transform3DComponent &transform) const;
	};
}

#endif //SURVIVE_TERRAINRENDERER_H
