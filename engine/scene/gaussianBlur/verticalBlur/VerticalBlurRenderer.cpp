//
// Created by david on 05. 12. 2020..
//

#include "VerticalBlurRenderer.h"
#include "VerticalBlurShader.h"
#include "Display.h"

Survive::VerticalBlurRenderer::VerticalBlurRenderer(int targetFboWidth, int targetFboHeight)
		: m_Width(targetFboWidth), m_Height(targetFboHeight),
		  m_VerticalBlurTexture(m_Fbo.createColorTexture(targetFboWidth, targetFboHeight))
{
	FrameBuffer::attachColorAttachment(m_VerticalBlurTexture.textureId());

	m_Shader.start();
	m_Shader.loadTargetHeight(static_cast<float>(targetFboHeight));
	VerticalBlurShader::stop();
}

void Survive::VerticalBlurRenderer::render(const Texture &texture, const Model &model) const
{
	m_Shader.start();
	texture.bindTexture(0);

	m_Fbo.bindDrawBuffer();
	glViewport(0, 0, m_Width, m_Height);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, model.m_VertexCount, GL_UNSIGNED_INT, nullptr);

	FrameBuffer::unbindDrawFrameBuffer();
	auto[width, height] = Display::getWindowSize<int>();
	glViewport(0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, 0);
	VerticalBlurShader::stop();
}

const Survive::Texture &Survive::VerticalBlurRenderer::getTexture() const
{
	return m_VerticalBlurTexture;
}
