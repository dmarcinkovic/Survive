//
// Created by david on 29. 03. 2020..
//

#include "TextShader.h"

Survive::TextShader::TextShader()
		: Shader(VERTEX_FILE, FRAGMENT_FILE)
{
	getUniformLocations();
}

void Survive::TextShader::getUniformLocations()
{
	m_LocationColor = glGetUniformLocation(m_Program, "color");
	m_LocationBorderColor = glGetUniformLocation(m_Program, "borderColor");
	m_LocationBorderWidth = glGetUniformLocation(m_Program, "borderWidth");
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
}

void Survive::TextShader::loadColor(const glm::vec3 &color) const
{
	loadVector3(m_LocationColor, color);
}

void Survive::TextShader::loadBorder(const glm::vec3 &borderColor, float borderWidth) const
{
	loadVector3(m_LocationBorderColor, borderColor);
	loadFloat(m_LocationBorderWidth, borderWidth);
}

void Survive::TextShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::TextShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}
