//
// Created by david on 22. 05. 2020..
//

#include "TerrainRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"

void TerrainRenderer::render(entt::registry &registry, const Camera &camera, const Light &light, GLuint shadowMap,
							 const glm::vec4 &plane) const
{
	auto group = registry.group<RenderComponent, Transform3DComponent, TexturedComponent>();
	if (group.empty())
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);
	group.each([&](RenderComponent &renderComponent, Transform3DComponent &transform, TexturedComponent &textures) {
		prepareRendering(renderComponent, textures);
		renderShadow(shadowMap, light);

		auto transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale,
																	  transform.rotation);

		m_Shader.loadTextures();
		m_Shader.loadTransformationMatrix(transformationMatrix);
		m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
		m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
		m_Shader.loadLightProjectionMatrix(Maths::lightProjectionMatrix);

		m_Shader.loadLight(light);
		m_Shader.loadPlane(plane);
		m_Shader.loadAddShadow(shadowMap != 0);

		glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
		finishRendering();
	});

	Renderer3DUtil::finishRendering();
}

void TerrainRenderer::renderShadow(GLuint shadowMap, const Light &light) const
{
	glm::mat4 lightView = Maths::createLightViewMatrix(light);
	m_Shader.loadLightViewMatrix(lightView);

	Texture texture(shadowMap);
	texture.bindTexture(5);
}

void TerrainRenderer::prepareRendering(const RenderComponent &renderComponent, const TexturedComponent &textures)
{
	Renderer3DUtil::prepareEntity(renderComponent.texturedModel);
	Renderer3DUtil::addTransparency(false, true);

	for (int i = 1; i <= textures.textures.size(); ++i)
	{
		textures.textures[i - 1].bindTexture(i);
	}
}

void TerrainRenderer::finishRendering()
{
	Texture::unbindTexture();

	Renderer3DUtil::addTransparency(true, false);
	Renderer3DUtil::finishRenderingEntity();
}
