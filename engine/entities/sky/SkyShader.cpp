//
// Created by david on 25. 12. 2020..
//

#include "SkyShader.h"

Survive::SkyShader::SkyShader()
		: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	getUniformLocations();
}

void Survive::SkyShader::getUniformLocations()
{
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");

	m_LocationPlane = glGetUniformLocation(m_Program, "plane");
}

void
Survive::SkyShader::loadViewAndProjectionMatrices(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::SkyShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::SkyShader::loadPlane(const glm::vec4 &plane) const
{
	loadVector4(m_LocationPlane, plane);
}
