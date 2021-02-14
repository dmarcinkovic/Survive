//
// Created by david on 05. 02. 2021..
//

#include "ParticleShader.h"

ParticleShader::ParticleShader()
		: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	getUniformLocations();
}

void ParticleShader::getUniformLocations()
{
	m_LocationNumberOfRows = glGetUniformLocation(m_Program, "numberOfRows");
	m_LocationNumberOfCols = glGetUniformLocation(m_Program, "numberOfCols");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
}

void ParticleShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void ParticleShader::loadDimensions(unsigned int rows, unsigned int cols) const
{
	loadUnsigned(m_LocationNumberOfRows, rows);
	loadUnsigned(m_LocationNumberOfCols, cols);
}
