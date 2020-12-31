//
// Created by david on 03. 05. 2020..
//

#include "ButtonShader.h"

ButtonShader::ButtonShader()
		: Shader(VERTEX_FILE, FRAGMENT_FILE)
{
	getUniformLocations();
}

void ButtonShader::getUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationColor = glGetUniformLocation(m_Program, "color");
	m_LocationIsLoadingImage = glGetUniformLocation(m_Program, "isLoadingImage");
}

void ButtonShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void ButtonShader::loadColor(const glm::vec4 &color) const
{
	loadVector4(m_LocationColor, color);
}

void ButtonShader::loadIsLoadingImage(bool value) const
{
	loadInteger(m_LocationIsLoadingImage, value);
}
