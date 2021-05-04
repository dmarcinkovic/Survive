//
// Created by david on 05. 12. 2020..
//

#include "HorizontalBlurRenderer.h"
#include "../../../core/display/Display.h"

Survive::HorizontalBlurRenderer::HorizontalBlurRenderer(int targetFboWidth, int targetFboHeight)
		: m_Width(targetFboWidth), m_Height(targetFboHeight),
		  m_HorizontalBlurTexture(m_Fbo.createColorTexture(targetFboWidth, targetFboHeight))
{
	FrameBuffer::attachColorAttachment(m_HorizontalBlurTexture.textureId());

	m_Shader.start();

	m_Shader.loadTargetWidth(static_cast<float >(targetFboWidth));
	HorizontalBlurShader::stop();
}

void Survive::HorizontalBlurRenderer::render(const Texture &texture, const Model &model) const
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
	HorizontalBlurShader::stop();
}

const Survive::Texture &Survive::HorizontalBlurRenderer::getTexture() const
{
	return m_HorizontalBlurTexture;
}
