//
// Created by david on 22. 05. 2020..
//

#include "TerrainRenderer.h"
#include "Maths.h"

void Survive::TerrainRenderer::render(entt::registry &registry, const Camera &camera, const Light &light,
									  GLuint shadowMap, const glm::vec4 &plane) const
{
	auto view = registry.view<Render3DComponent, Transform3DComponent,
							  TexturedComponent, TagComponent>(entt::exclude<MoveComponent>);
	if (view.begin() == view.end())
	{
		return;
	}

	prepareRendering(m_Shader);
	glEnable(GL_STENCIL_TEST);
	for (auto const &entity: view)
	{
		const Render3DComponent &renderComponent = view.get<Render3DComponent>(entity);
		const Transform3DComponent &transform = view.get<Transform3DComponent>(entity);
		const TexturedComponent &textures = view.get<TexturedComponent>(entity);

		prepareRenderingTerrain(renderComponent, textures);
		renderShadow(shadowMap, light);

		loadUniforms(camera, light, plane, transform);
		drawOutline(registry, entity);
		m_Shader.loadAddShadow(shadowMap != 0);

		glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);
		finishRenderingTerrain();
	}

	finishRendering();
	glDisable(GL_STENCIL_TEST);
}

void Survive::TerrainRenderer::renderShadow(GLuint shadowMap, const Light &light) const
{
	m_Shader.loadLightViewMatrix(light.getViewMatrix());

	Texture texture(shadowMap);
	texture.bindTexture(5);
}

void Survive::TerrainRenderer::prepareRenderingTerrain(const Render3DComponent &renderComponent,
													   const TexturedComponent &textures)
{
	constexpr int numberOfVaoUnits = 3;
	prepareEntity(renderComponent.texturedModel, numberOfVaoUnits);
	addTransparency(false, true);

	for (int i = 1; i <= textures.textures.size(); ++i)
	{
		textures.textures[i - 1].bindTexture(i);
	}
}

void Survive::TerrainRenderer::finishRenderingTerrain()
{
	constexpr int numberOfVaoUnits = 3;
	Texture::unbindTexture();

	addTransparency(true, false);
	finishRenderingEntity(numberOfVaoUnits);
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
