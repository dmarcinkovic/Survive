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
	m_LocationTargetHeights = glGetUniformLocation(m_Program, "targetHeight");
}
