//
// Created by david on 27. 12. 2020..
//

#include "OutlineRenderer.h"
#include "OutlineComponent.h"
#include "Maths.h"

void Survive::OutlineRenderer::render(entt::registry &registry, const Camera &camera) const
{
	auto view = registry.view<OutlineComponent, Render3DComponent, Transform3DComponent>();

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
		if (!outline.drawOutline)
		{
			continue;
		}

		const Render3DComponent &renderComponent = view.get<Render3DComponent>(entity);
		const Transform3DComponent &transform = view.get<Transform3DComponent>(entity);

		prepareObject(renderComponent);
		loadUniforms(transform, camera);

		GLsizei count = renderComponent.texturedModel.vertexCount();
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

	glm::vec3 rotation = transform.rotation + camera.rotation;
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale, rotation);

	m_Shader.loadTransformationMatrix(modelMatrix);

	float distanceFromCamera = glm::length(transform.position - camera.position);

	constexpr float constant = 4e-3;
	glm::vec3 factor = constant * distanceFromCamera / transform.scale;

	m_Shader.loadFactor(factor);
}

void Survive::OutlineRenderer::prepareObject(const Render3DComponent &renderComponent)
{
	glBindVertexArray(renderComponent.texturedModel.vaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);
}

void Survive::OutlineRenderer::finishRenderingObject()
{
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
}
