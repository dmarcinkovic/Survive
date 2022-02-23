//
// Created by david on 22. 05. 2020..
//

#include "TerrainRenderer.h"
#include "Maths.h"
#include "Renderer3D.h"

void
Survive::TerrainRenderer::render(entt::registry &registry, const Camera &camera, const Light &light, GLuint shadowMap,
								 const glm::vec4 &plane) const
{
	auto view = registry.view<Render3DComponent, Transform3DComponent, TexturedComponent>(entt::exclude<MoveComponent>);
	if (view.begin() == view.end())
	{
		return;
	}

	Renderer3D::prepareRendering(m_Shader);
	view.each([&](Render3DComponent &renderComponent, Transform3DComponent &transform, TexturedComponent &textures) {
		prepareRendering(renderComponent, textures);
		renderShadow(shadowMap, light);

		loadUniforms(camera, light, plane, transform);
		m_Shader.loadAddShadow(shadowMap != 0);

		glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
		finishRendering();
	});

	Renderer3D::finishRendering();
}

void Survive::TerrainRenderer::renderShadow(GLuint shadowMap, const Light &light) const
{
	m_Shader.loadLightViewMatrix(light.getViewMatrix());

	Texture texture(shadowMap);
	texture.bindTexture(5);
}

void
Survive::TerrainRenderer::prepareRendering(const Render3DComponent &renderComponent, const TexturedComponent &textures)
{
	Renderer3D::prepareEntity(renderComponent.texturedModel);
	Renderer3D::addTransparency(false, true);

	for (int i = 1; i <= textures.textures.size(); ++i)
	{
		textures.textures[i - 1].bindTexture(i);
	}
}

void Survive::TerrainRenderer::finishRendering()
{
	Texture::unbindTexture();

	Renderer3D::addTransparency(true, false);
	Renderer3D::finishRenderingEntity();
}

void Survive::TerrainRenderer::loadUniforms(const Camera &camera, const Light &light, const glm::vec4 &plane,
											const Transform3DComponent &transform) const
{
	auto transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale,
																  transform.rotation);

	m_Shader.loadTextures();
	m_Shader.loadTransformationMatrix(transformationMatrix);
	m_Shader.loadViewMatrix(camera.getViewMatrix());
	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_Shader.loadLightProjectionMatrix(camera.getLightProjectionMatrix());

	m_Shader.loadLight(light);
	m_Shader.loadPlane(plane);
}
