//
// Created by david on 05. 12. 2020..
//

#include "HorizontalBlurShader.h"

Survive::HorizontalBlurShader::HorizontalBlurShader()
		: Shader(vertexShaderSource, fragmentShaderSource)
{
	loadUniformLocations();
}

void Survive::HorizontalBlurShader::loadUniformLocations()
{
	m_LocationTargetWidth = glGetUniformLocation(m_Program, "targetWidth");
}

void Survive::HorizontalBlurShader::loadTargetWidth(float targetWidth) const
{
	loadFloat(m_LocationTargetWidth, targetWidth);
}
