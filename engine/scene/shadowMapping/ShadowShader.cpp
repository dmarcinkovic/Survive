//
// Created by david on 22. 05. 2020..
//

#include "ShadowShader.h"

Survive::ShadowShader::ShadowShader()
		: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	getUniformLocations();
}

void Survive::ShadowShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::ShadowShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::ShadowShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void Survive::ShadowShader::getUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
}
