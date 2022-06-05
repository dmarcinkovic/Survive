//
// Created by david on 05. 12. 2020..
//

#include "VerticalBlurShader.h"

Survive::VerticalBlurShader::VerticalBlurShader()
		: Shader(vertexShaderSource, fragmentShaderSource)
{
	loadUniformLocations();
}

void Survive::VerticalBlurShader::loadUniformLocations()
{
	m_LocationTargetHeight = glGetUniformLocation(m_Program, "targetHeight");
}

void Survive::VerticalBlurShader::loadTargetHeight(float targetHeight) const
{
	loadFloat(m_LocationTargetHeight, targetHeight);
}
