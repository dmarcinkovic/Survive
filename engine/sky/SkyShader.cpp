//
// Created by david on 25. 12. 2020..
//

#include "SkyShader.h"

SkyShader::SkyShader()
		: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	getUniformLocations();
}

void SkyShader::getUniformLocations()
{
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
}

void SkyShader::loadViewAndProjectionMatrices(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}
