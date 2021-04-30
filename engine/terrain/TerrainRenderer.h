//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAINRENDERER_H
#define SURVIVE_TERRAINRENDERER_H

#include "TerrainShader.h"
#include "../camera/Camera.h"
#include "../light/Light.h"
#include "../../ecs/entt.hpp"
#include "../components/Components.h"

class TerrainRenderer
{
private:
	TerrainShader m_Shader;

public:
	void render(entt::registry &registry, const Camera &camera, const Light &light, GLuint shadowMap,
				const glm::vec4 &plane = glm::vec4{}) const;

private:
	static void prepareRendering(const RenderComponent &renderComponent, const TexturedComponent &textures);

	static void finishRendering();

	void renderShadow(GLuint shadowMap, const Light &light) const;

	void loadUniforms(const Camera &camera, const Light &light, const glm::vec4 &plane,
					  const Transform3DComponent &transform) const;
};


#endif //SURVIVE_TERRAINRENDERER_H
