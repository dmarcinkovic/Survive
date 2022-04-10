//
// Created by david on 27. 12. 2020..
//

#include "OutlineShader.h"

Survive::OutlineShader::OutlineShader()
		: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	loadUniformLocations();
}

void Survive::OutlineShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::OutlineShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void Survive::OutlineShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::OutlineShader::loadUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");

	m_LocationFactor = glGetUniformLocation(m_Program, "factor");
}

void Survive::OutlineShader::loadFactor(float factor) const
{
	loadFloat(m_LocationFactor, factor);
}
