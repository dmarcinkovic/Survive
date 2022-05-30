//
// Created by david on 05. 02. 2021..
//

#include "ParticleShader.h"

Survive::ParticleShader::ParticleShader()
		: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	getUniformLocations();
}

void Survive::ParticleShader::getUniformLocations()
{
	m_LocationNumberOfRows = glGetUniformLocation(m_Program, "numberOfRows");
	m_LocationNumberOfCols = glGetUniformLocation(m_Program, "numberOfCols");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");

	m_LocationColor = glGetUniformLocation(m_Program, "color");
}

void Survive::ParticleShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::ParticleShader::loadDimensions(unsigned int rows, unsigned int cols) const
{
	loadUnsigned(m_LocationNumberOfRows, rows);
	loadUnsigned(m_LocationNumberOfCols, cols);
}

void Survive::ParticleShader::loadColor(const glm::vec4 &color) const
{
	loadVector4(m_LocationColor, color);
}
