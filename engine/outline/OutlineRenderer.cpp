//
// Created by david on 27. 12. 2020..
//

#include "OutlineRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"
#include "../components/OutlineComponent.h"

void OutlineRenderer::render(const entt::registry &registry, const Camera &camera) const
{
	if (!m_Render)
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);
	glEnable(GL_STENCIL_TEST);
	setStencilFunctions();

	RenderComponent renderComponent = registry.get<RenderComponent>(m_Entity);
	Transform3DComponent transform = registry.get<Transform3DComponent>(m_Entity);

	prepareObject(renderComponent);
	loadUniforms(transform, camera);

	glDrawArrays(GL_TRIANGLES, 0, renderComponent.texturedModel.vertexCount());

	finishRenderingObject();

	resetStencilFunctions();
	Renderer3DUtil::finishRendering();
	glDisable(GL_STENCIL_TEST);
}

void OutlineRenderer::add3DObject(entt::registry &registry, entt::entity entity)
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

void OutlineRenderer::removeObject(entt::registry &registry)
{
	OutlineComponent &outline = registry.get<OutlineComponent>(m_Entity);
	outline.drawOutline = false;

	m_Render = false;
}

void OutlineRenderer::setStencilFunctions()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
}

void OutlineRenderer::resetStencilFunctions()
{
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
}

void OutlineRenderer::loadUniforms(const Transform3DComponent &transform, const Camera &camera) const
{
	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);

	glm::vec3 rotation = transform.rotation + camera.m_Rotation;
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(transform.position, transform.scale * SCALE, rotation);
	m_Shader.loadTransformationMatrix(modelMatrix);
}

void OutlineRenderer::prepareObject(const RenderComponent &renderComponent)
{
	glBindVertexArray(renderComponent.texturedModel.vaoID());
	glEnableVertexAttribArray(0);
}

void OutlineRenderer::finishRenderingObject()
{
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}
