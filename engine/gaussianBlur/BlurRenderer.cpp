//
// Created by david on 19. 12. 2020..
//

#include "BlurRenderer.h"

BlurRenderer::BlurRenderer(int width, int height)
		: m_Model(m_Loader.renderQuad()), m_HorizontalBlurRenderer(width, height, m_Model),
		  m_VerticalBlurRenderer(width, height), m_Texture(m_Fbo.createTexture())
{

}

void BlurRenderer::render() const
{

}

const Texture &BlurRenderer::getTexture() const
{
	return m_Texture;
}
