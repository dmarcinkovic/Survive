//
// Created by david on 27. 12. 2020..
//

#include "OutlineRenderer.h"
#include "Components.h"
#include "Maths.h"

void Survive::OutlineRenderer::render(entt::registry &registry, const Camera &camera) const
{
	auto view = registry.view<OutlineComponent, Transform3DComponent>();

	if (view.begin() == view.end())
	{
		return;
	}

	prepareRendering(m_Shader);
	glEnable(GL_STENCIL_TEST);
	setStencilFunctions();

	for (auto const &entity: view)
	{
		const OutlineComponent &outline = view.get<OutlineComponent>(entity);
		if (!outline.drawOutline || !registry.any_of<Render3DComponent, TerrainComponent>(entity))
		{
			continue;
		}

		TexturedModel model = getModel(registry, entity);
		prepareObject(model);

		const Transform3DComponent &transform = view.get<Transform3DComponent>(entity);
		loadUniforms(transform, camera);

		GLsizei count = model.vertexCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

		finishRenderingObject();
	}

	resetStencilFunctions();
	finishRendering();
	glDisable(GL_STENCIL_TEST);
}

void Survive::OutlineRenderer::setStencilFunctions()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
}

void Survive::OutlineRenderer::resetStencilFunctions()
{
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
}

void Survive::OutlineRenderer::loadUniforms(const Transform3DComponent &transform, const Camera &camera) const
{
	m_Shader.loadViewMatrix(camera.getViewMatrix());
	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, transform.rotation);

	m_Shader.loadTransformationMatrix(modelMatrix);

	float distanceFromCamera = glm::length(transform.position - camera.getPosition());

	constexpr float constant = 4e-3;
	glm::vec3 factor = constant * distanceFromCamera / transform.scale;

	m_Shader.loadFactor(factor);
}

void Survive::OutlineRenderer::prepareObject(const TexturedModel &model)
{
	glBindVertexArray(model.vaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
}

void Survive::OutlineRenderer::finishRenderingObject()
{
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}

Survive::TexturedModel Survive::OutlineRenderer::getModel(const entt::registry &registry, entt::entity entity)
{
	if (registry.any_of<Render3DComponent>(entity))
	{
		return registry.get<Render3DComponent>(entity).texturedModel;
	} else if (registry.any_of<TerrainComponent>(entity))
	{
		return registry.get<TerrainComponent>(entity).terrainModel;
	}

	return {};
}
