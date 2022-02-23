//
// Created by david on 27. 12. 2020..
//

#include "OutlineRenderer.h"
#include "OutlineComponent.h"
#include "Maths.h"
#include "Renderer3D.h"

void Survive::OutlineRenderer::render(const entt::registry &registry, const Camera &camera) const
{
	if (!m_Render)
	{
		return;
	}

	Renderer3D::prepareRendering(m_Shader);
	glEnable(GL_STENCIL_TEST);
	setStencilFunctions();

	const Render3DComponent &renderComponent = registry.get<Render3DComponent>(m_Entity);
	const Transform3DComponent &transform = registry.get<Transform3DComponent>(m_Entity);

	prepareObject(renderComponent);
	loadUniforms(transform, camera);

	glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);

	finishRenderingObject();

	resetStencilFunctions();
	Renderer3D::finishRendering();
	glDisable(GL_STENCIL_TEST);
}

void Survive::OutlineRenderer::add3DObject(entt::registry &registry, entt::entity entity)
{
	if (m_Render)
	{
		OutlineComponent &previousOutline = registry.get<OutlineComponent>(m_Entity);
		previousOutline.drawOutline = false;
	}

	m_Entity = entity;

	m_Render = true;
	registry.emplace<OutlineComponent>(entity, true);
}

void Survive::OutlineRenderer::removeObject(entt::registry &registry)
{
	OutlineComponent &outline = registry.get<OutlineComponent>(m_Entity);
	outline.drawOutline = false;

	m_Render = false;
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
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale * SCALE, rotation);

	m_Shader.loadTransformationMatrix(modelMatrix);
}

void Survive::OutlineRenderer::prepareObject(const Render3DComponent &renderComponent)
{
	glBindVertexArray(renderComponent.texturedModel.vaoID());
	glEnableVertexAttribArray(0);
}

void Survive::OutlineRenderer::finishRenderingObject()
{
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}
