//
// Created by david on 03. 05. 2020..
//

#include "ButtonShader.h"

Survive::ButtonShader::ButtonShader()
		: Shader(vertexShaderSource, fragmentShaderSource)
{
	getUniformLocations();
}

void Survive::ButtonShader::getUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationColor = glGetUniformLocation(m_Program, "color");
	m_LocationIsLoadingImage = glGetUniformLocation(m_Program, "isLoadingImage");
}

void Survive::ButtonShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::ButtonShader::loadColor(const glm::vec4 &color) const
{
	loadVector4(m_LocationColor, color);
}

void Survive::ButtonShader::loadIsLoadingImage(bool value) const
{
	loadInteger(m_LocationIsLoadingImage, value);
}
