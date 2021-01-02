//
// Created by david on 05. 12. 2020..
//

#include "VerticalBlurShader.h"

VerticalBlurShader::VerticalBlurShader()
	: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	loadUniformLocations();
}

void VerticalBlurShader::loadUniformLocations()
{
	m_LocationTargetHeight = glGetUniformLocation(m_Program, "targetHeight");
}

void VerticalBlurShader::loadTargetHeight(float targetHeight) const
{
	loadFloat(m_LocationTargetHeight, targetHeight);
}
