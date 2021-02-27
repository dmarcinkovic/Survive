//
// Created by david on 03. 05. 2020..
//

#include "Renderer2DUtil.h"

void Renderer2DUtil::prepareRendering(const Shader &shader)
{
	shader.start();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
}

void Renderer2DUtil::finishRendering()
{
	Shader::stop();
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void Renderer2DUtil::prepareEntity(const TexturedModel &texture, int numberOfVertexUnits)
{
	texture.bind();

	for (int vaoUnit = 0; vaoUnit < numberOfVertexUnits; ++vaoUnit)
	{
		glEnableVertexAttribArray(vaoUnit);
	}
}

void Renderer2DUtil::finishRenderingEntity(int numberOfVertexUnits)
{
	TexturedModel::unbind();

	for (int vaoUnit = numberOfVertexUnits - 1; vaoUnit >= 0; --vaoUnit)
	{
		glDisableVertexAttribArray(vaoUnit);
	}

	Loader::unbindVao();
}
