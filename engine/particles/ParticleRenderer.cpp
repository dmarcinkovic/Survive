//
// Created by david on 11. 02. 2021..
//

#include <glm/ext/matrix_transform.hpp>

#include "ParticleRenderer.h"
#include "../renderer/Renderer2DUtil.h"
#include "../math/Maths.h"

int ParticleRenderer::pointer = 0;

ParticleRenderer::ParticleRenderer()
		: m_Vbo(m_Loader.createEmptyVBO(INSTANCE_DATA_LENGTH * MAX_INSTANCES))
{
}

void ParticleRenderer::render(const Camera &camera) const
{
	prepare();
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);

	for (auto const&[particleModel, particles] : m_Particles)
	{
		if (particles.empty())
		{
			continue;
		}

		Renderer2DUtil::prepareEntity(particleModel.texturedModel, VAO_UNITS);

		m_Shader.loadDimensions(particles.back().m_Rows, particles.back().m_Cols);

		std::vector<float> data = updateParticles(particles, viewMatrix);

		Loader::updateVBO(m_Vbo, data, particles.size() * INSTANCE_DATA_LENGTH);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, particleModel.texturedModel.vertexCount(), particles.size());

		Renderer2DUtil::finishRenderingEntity(VAO_UNITS);
	}

	finish();
}

std::vector<float>
ParticleRenderer::updateParticles(const std::vector<Particle> &particles, const glm::mat4 &viewMatrix)
{
	pointer = 0;
	std::vector<float> data(particles.size() * INSTANCE_DATA_LENGTH);

	for (auto const &particle : particles)
	{
		updateModelViewMatrix(particle.m_Position, particle.m_Rotation, particle.m_Scale, viewMatrix, data);
		updateTextureCoordinates(particle, data);
	}

	return data;
}

void ParticleRenderer::prepare() const
{
	m_Shader.start();

	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	glEnable(GL_DEPTH_TEST);

	enableBlending();
}

void ParticleRenderer::finish()
{
	Shader::stop();

	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(true);
}

void ParticleRenderer::enableBlending()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(false);
}

void
ParticleRenderer::updateModelViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale,
										const glm::mat4 &viewMatrix, std::vector<float> &data)
{
	glm::mat4 modelMatrix{1};

	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix[0][0] = viewMatrix[0][0];
	modelMatrix[0][1] = viewMatrix[1][0];
	modelMatrix[0][2] = viewMatrix[2][0];
	modelMatrix[1][0] = viewMatrix[0][1];
	modelMatrix[1][1] = viewMatrix[1][1];
	modelMatrix[1][2] = viewMatrix[2][1];
	modelMatrix[2][0] = viewMatrix[0][2];
	modelMatrix[2][1] = viewMatrix[1][2];
	modelMatrix[2][2] = viewMatrix[2][2];

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3{0, 0, 1});
	modelMatrix = glm::scale(modelMatrix, scale);

	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	storeMatrixData(modelViewMatrix, data);
}

void ParticleRenderer::storeMatrixData(const glm::mat4 &matrix, std::vector<float> &data)
{
	data[pointer++] = matrix[0][0];
	data[pointer++] = matrix[0][1];
	data[pointer++] = matrix[0][2];
	data[pointer++] = matrix[0][3];
	data[pointer++] = matrix[1][0];
	data[pointer++] = matrix[1][1];
	data[pointer++] = matrix[1][2];
	data[pointer++] = matrix[1][3];
	data[pointer++] = matrix[2][0];
	data[pointer++] = matrix[2][1];
	data[pointer++] = matrix[2][2];
	data[pointer++] = matrix[2][3];
	data[pointer++] = matrix[3][0];
	data[pointer++] = matrix[3][1];
	data[pointer++] = matrix[3][2];
	data[pointer++] = matrix[3][3];
}

void ParticleRenderer::updateTextureCoordinates(const Particle &particle, std::vector<float> &data)
{
	data[pointer++] = particle.m_TextureOffset1.x;
	data[pointer++] = particle.m_TextureOffset1.y;
	data[pointer++] = particle.m_TextureOffset2.x;
	data[pointer++] = particle.m_TextureOffset2.y;
	data[pointer++] = particle.m_BlendFactor;
}

void ParticleRenderer::addInstanceAttributes(const TexturedModel &model) const
{
	Loader::addInstancedAttribute(model.vaoID(), m_Vbo, 1, 4, INSTANCE_DATA_LENGTH, 0);
	Loader::addInstancedAttribute(model.vaoID(), m_Vbo, 2, 4, INSTANCE_DATA_LENGTH, 4);
	Loader::addInstancedAttribute(model.vaoID(), m_Vbo, 3, 4, INSTANCE_DATA_LENGTH, 8);
	Loader::addInstancedAttribute(model.vaoID(), m_Vbo, 4, 4, INSTANCE_DATA_LENGTH, 12);
	Loader::addInstancedAttribute(model.vaoID(), m_Vbo, 5, 4, INSTANCE_DATA_LENGTH, 16);
	Loader::addInstancedAttribute(model.vaoID(), m_Vbo, 6, 1, INSTANCE_DATA_LENGTH, 20);
}

std::vector<Particle> &ParticleRenderer::getParticles(const ParticleModel &model)
{
	std::vector<Particle> &particles = m_Particles[model];

	if (particles.empty())
	{
		addInstanceAttributes(model.texturedModel);
	}

	return particles;
}
