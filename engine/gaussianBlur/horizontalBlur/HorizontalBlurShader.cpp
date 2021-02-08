//
// Created by david on 05. 12. 2020..
//

#include "HorizontalBlurShader.h"

HorizontalBlurShader::HorizontalBlurShader()
	: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	loadUniformLocations();
}

void HorizontalBlurShader::loadUniformLocations()
{
	m_LocationTargetWidth = glGetUniformLocation(m_Program, "targetWidth");
}

void HorizontalBlurShader::loadTargetWidth(float targetWidth) const
{
	loadFloat(m_LocationTargetWidth, targetWidth);
}
