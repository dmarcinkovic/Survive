//
// Created by david on 27. 12. 2020..
//

#include "OutlineRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"

void OutlineRenderer::render(const Camera &camera) const
{
	Renderer3DUtil::prepareRendering(m_Shader);
	setStencilFunctions();

	Renderer3DUtil::prepareEntity(m_Object->m_Texture);
	loadUniforms(camera);

	glDrawArrays(GL_TRIANGLES, 0, m_Object->m_Texture.vertexCount());

	Renderer3DUtil::finishRenderingEntity();

	resetStencilFunctions();
	Renderer3DUtil::finishRendering();
}

void OutlineRenderer::add3DObject(Object3D &object)
{
	m_Object = &object;
}

void OutlineRenderer::setStencilFunctions()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
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
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(m_Object->m_Position, m_Object->m_ScaleX * SCALE,
															  m_Object->m_ScaleY * SCALE,
															  m_Object->m_ScaleZ * SCALE, rotation.x, rotation.y,
															  rotation.z);
	m_Shader.loadTransformationMatrix(modelMatrix);
}
