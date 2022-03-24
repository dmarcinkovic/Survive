//
// Created by david on 17. 05. 2020..
//

#include "Renderer3D.h"

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

void Survive::Renderer3D::prepareEntity(const TexturedModel &texture)
{
	texture.bind();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
}

void Survive::Renderer3D::finishRenderingEntity()
{
	TexturedModel::unbind();

	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

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
