//
// Created by david on 27. 12. 2020..
//

#include "OutlineRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"

OutlineRenderer::OutlineRenderer(const Light &light)
	: m_Light(light)
{

}

void OutlineRenderer::render(const Camera &camera) const
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDisable(GL_DEPTH_TEST);
	m_Shader.start();

	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);

	// TODO change this to render only one object. No need to iterate and calculate hash because only one object
	// TODO can be selected at the time
	for (auto const&[texturedModel, objects] : m_Objects)
	{
		Renderer3DUtil::prepareEntity(texturedModel);

		for (auto const &object : objects)
		{
			auto const &o = object.get();
			auto rotation = camera.m_Rotation + o.m_Rotation;

			glm::mat4 modelMatrix = Maths::createTransformationMatrix(o.m_Position, o.m_ScaleX, o.m_ScaleY,
																	  o.m_ScaleZ, rotation.x, rotation.y, rotation.z);
			m_Shader.loadTransformationMatrix(modelMatrix);
			if (o.m_DrawOutline)
			{
				glStencilFunc(GL_ALWAYS, 1, 0xFF);
				glStencilMask(0xFF);
			}

			Renderer3DUtil::addTransparency(!o.m_IsTransparent, !o.m_IsTransparent);

			glDrawArrays(GL_TRIANGLES, 0, o.m_Texture.vertexCount());

			Renderer3DUtil::addTransparency(o.m_IsTransparent, o.m_IsTransparent);
		}

		Renderer3DUtil::finishRenderingEntity();
	}

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	Renderer3DUtil::finishRendering();
}

void OutlineRenderer::add3DObject(Object3D &object)
{
	auto &batch = m_Objects[object.m_Texture];
	batch.emplace_back(object);
}
