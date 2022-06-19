//
// Created by david on 17. 05. 2020..
//

#include "Renderer3D.h"
#include "OutlineComponent.h"

void Survive::Renderer3D::prepareRendering(const Shader &shader)
{
	shader.start();
	glEnable(GL_DEPTH_TEST);
}

void Survive::Renderer3D::finishRendering()
{
	Shader::stop();
	glDisable(GL_DEPTH_TEST);
}

void Survive::Renderer3D::prepareEntity(const TexturedModel &texture, int numberOfVaoUnits)
{
	texture.bind();

	for (int vaoUnit = 0; vaoUnit < numberOfVaoUnits; ++vaoUnit)
	{
		glEnableVertexAttribArray(vaoUnit);
	}
}

void Survive::Renderer3D::finishRenderingEntity(int numberOfVaoUnits)
{
	TexturedModel::unbind();

	for (int vaoUnit = 0; vaoUnit < numberOfVaoUnits; ++vaoUnit)
	{
		glDisableVertexAttribArray(vaoUnit);
	}

	Loader::unbindVao();
}

void Survive::Renderer3D::addTransparency(bool cullFace, bool blend)
{
	if (cullFace)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	} else
	{
		glDisable(GL_CULL_FACE);
	}

	if (blend)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	} else
	{
		glDisable(GL_BLEND);
	}
}

void Survive::Renderer3D::drawOutline(const entt::registry &registry, entt::entity entity)
{
	if (registry.any_of<OutlineComponent>(entity))
	{
		const OutlineComponent &outline = registry.get<OutlineComponent>(entity);
		if (outline.drawOutline)
		{
			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);
		}
	} else
	{
		glStencilMask(0x00);
	}
}