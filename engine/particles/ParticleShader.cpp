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
}

void ParticleShader::loadNumberOfRows(int rows) const
{
	loadInteger(m_LocationNumberOfRows, rows);
}
