//
// Created by david on 11. 02. 2021..
//

#include "ParticleRenderer.h"
#include "../renderer/Renderer2DUtil.h"

void ParticleRenderer::render(const Camera &camera) const
{
	prepare();

	for (auto const&[texturedModel, particles] : m_Particles)
	{
		Renderer2DUtil::prepareEntity(texturedModel, VAO_UNITS);




		Renderer2DUtil::finishRenderingEntity(VAO_UNITS);
	}

	finish();
}

void ParticleRenderer::prepare() const
{
	m_Shader.start();
	enableBlending();
}

void ParticleRenderer::finish()
{
	Shader::stop();

	glDisable(GL_BLEND);
}

void ParticleRenderer::enableBlending()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(false);
}
