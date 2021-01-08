//
// Created by david on 27. 12. 2020..
//

#include "OutlineRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"

void OutlineRenderer::render(const Camera &camera) const
{
	if (m_Object == nullptr)
	{
		return;
	}

	Renderer3DUtil::prepareRendering(m_Shader);
	setStencilFunctions();

	prepareObject();
	loadUniforms(camera);

	glDrawArrays(GL_TRIANGLES, 0, m_Object->m_Texture.vertexCount());

	finishRenderingObject();

	resetStencilFunctions();
	Renderer3DUtil::finishRendering();
}

void OutlineRenderer::add3DObject(Object3D &object)
{
	if (m_Object != nullptr)
	{
		m_Object->m_DrawOutline = false;
	}

	m_Object = &object;
	m_Object->m_DrawOutline = true;
}

void OutlineRenderer::removeObject()
{
	m_Object->m_DrawOutline = false;
	m_Object = nullptr;
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

void OutlineRenderer::loadUniforms(const Camera &camera) const
{
	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);

	auto rotation = m_Object->m_Rotation + camera.m_Rotation;
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(m_Object->m_Position, m_Object->m_Scale * SCALE,
															  rotation);
	m_Shader.loadTransformationMatrix(modelMatrix);
}

void OutlineRenderer::prepareObject() const
{
	glBindVertexArray(m_Object->m_Texture.vaoID());
	glEnableVertexAttribArray(0);
}

void OutlineRenderer::finishRenderingObject()
{
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}