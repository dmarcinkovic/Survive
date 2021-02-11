//
// Created by david on 11. 02. 2021..
//

#include <glm/ext/matrix_transform.hpp>
#include "ParticleRenderer.h"
#include "../renderer/Renderer2DUtil.h"

int ParticleRenderer::pointer = 0;

void ParticleRenderer::render(const Camera &camera) const
{
	prepare();

	for (auto const&[texturedModel, particles] : m_Particles)
	{
		Renderer2DUtil::prepareEntity(texturedModel, VAO_UNITS);

		m_Shader.loadNumberOfRows(particles.back().numberOfRows());

		pointer = 0;
		std::vector<float> data(particles.size() * INSTANCE_DATA_LENGTH);

		for (auto const &particle : particles)
		{

		}

		glDrawElementsInstanced(GL_TRIANGLES, texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr, particles.size());

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

void
ParticleRenderer::updateModelViewMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale,
										const glm::mat4 &viewMatrix, std::vector<float> &data)
{
	// TODO this is just creating model matrix and view matrix
	// TODO first 3x3 sub-matrix has to be identity matrix
	// TODO do this calculation in the vertex shader
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
