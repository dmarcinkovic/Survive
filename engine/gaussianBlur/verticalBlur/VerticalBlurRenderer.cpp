//
// Created by david on 05. 12. 2020..
//

#include "VerticalBlurRenderer.h"
#include "VerticalBlurShader.h"
#include "../../display/Display.h"

VerticalBlurRenderer::VerticalBlurRenderer(int targetFboWidth, int targetFboHeight, const Model &model)
		: m_Width(targetFboWidth), m_Height(targetFboHeight), m_Model(model),
		verticalBlurTexture(m_Fbo.createColorTexture(targetFboWidth, targetFboHeight))
{
	FrameBuffer::attachColorAttachment(verticalBlurTexture);

	m_Shader.start();
	m_Shader.loadTargetHeight(static_cast<float>(targetFboHeight));
	VerticalBlurShader::stop();
}

void VerticalBlurRenderer::render(const Texture &texture) const
{
	m_Shader.start();
	texture.bindTexture(0);

//	m_Fbo.bindFrameBuffer();
	glViewport(0, 0, m_Width, m_Height);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, m_Model.m_VertexCount, GL_UNSIGNED_INT, nullptr);

	FrameBuffer::unbindFrameBuffer();
	auto[width, height] = Display::getWindowSize();
	glViewport(0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, 0);
	VerticalBlurShader::stop();
}

GLuint VerticalBlurRenderer::getTexture() const
{
	return verticalBlurTexture;
}
