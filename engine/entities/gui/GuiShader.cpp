//
// Created by david on 28. 03. 2020..
//

#include "GuiShader.h"

Survive::GuiShader::GuiShader()
		: Shader(VERTEX_FILE, FRAGMENT_FILE)
{
	getUniformLocations();
}

void Survive::GuiShader::getUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
	m_LocationColor = glGetUniformLocation(m_Program, "color");
}

void Survive::GuiShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::GuiShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::GuiShader::loadColor(const glm::vec4 &color) const
{
	loadVector4(m_LocationColor, color);
}
