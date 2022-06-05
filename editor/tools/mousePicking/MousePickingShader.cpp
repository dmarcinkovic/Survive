//
// Created by david on 12. 01. 2021..
//

#include "MousePickingShader.h"

Survive::MousePickingShader::MousePickingShader()
		: Shader(vertexShaderSource, fragmentShaderSource)
{
	getUniformLocations();
}

void Survive::MousePickingShader::getUniformLocations()
{
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
	m_LocationPickingColor = glGetUniformLocation(m_Program, "pickingColor");
}

void Survive::MousePickingShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::MousePickingShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void Survive::MousePickingShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::MousePickingShader::loadPickingColor(const glm::vec4 &pickingColor) const
{
	loadVector4(m_LocationPickingColor, pickingColor);
}
