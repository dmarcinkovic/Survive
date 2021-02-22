//
// Created by david on 22. 02. 2021..
//

#include "WaterShader.h"

WaterShader::WaterShader()
	: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	loadUniformLocations();
}

void WaterShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void WaterShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void WaterShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void WaterShader::loadUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
}
