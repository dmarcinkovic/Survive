//
// Created by david on 11. 02. 2021..
//

#include "ParticleRenderer.h"

void ParticleRenderer::render(const Camera &camera)
{

}

void ParticleRenderer::prepare()
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
