//
// Created by david on 05. 12. 2020..
//

#include "HorizontalBlurRenderer.h"
#include "../../display/Display.h"

HorizontalBlurRenderer::HorizontalBlurRenderer(int targetFboWidth, int targetFboHeight, const Model &model)
		: m_Width(targetFboWidth), m_Height(targetFboHeight), m_Model(model),
		  m_HorizontalBlurTexture(m_Fbo.createColorTexture(targetFboWidth, targetFboHeight))
{
	FrameBuffer::attachColorAttachment(m_HorizontalBlurTexture.textureId());

	m_Shader.start();

	m_Shader.loadTargetWidth(static_cast<float >(targetFboWidth));
	HorizontalBlurShader::stop();
}

void HorizontalBlurRenderer::render(const Texture &texture) const
{
	m_Shader.start();
	texture.bindTexture(0);

	m_Fbo.bindDrawBuffer();
	glViewport(0, 0, m_Width, m_Height);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawElements(GL_TRIANGLES, m_Model.m_VertexCount, GL_UNSIGNED_INT, nullptr);

	FrameBuffer::unbindDrawFrameBuffer();
	auto[width, height] = Display::getWindowSize();
	glViewport(0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, 0);
	HorizontalBlurShader::stop();
}

const Texture &HorizontalBlurRenderer::getTexture() const
{
	return m_HorizontalBlurTexture;
}
