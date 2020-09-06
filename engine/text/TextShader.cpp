//
// Created by david on 29. 03. 2020..
//

#include "TextShader.h"

TextShader::TextShader()
        : Shader(VERTEX_FILE, FRAGMENT_FILE)
{
    getUniformLocations();
}

void TextShader::getUniformLocations()
{
    m_LocationColor = glGetUniformLocation(m_Program, "color");
    m_LocationBorderColor = glGetUniformLocation(m_Program, "borderColor");
    m_LocationBorderWidth = glGetUniformLocation(m_Program, "borderWidth");
}

void TextShader::loadColor(const glm::vec3 &color) const
{
    loadVector3(m_LocationColor, color);
}

void TextShader::loadBorder(const glm::vec3 &borderColor, float borderWidth) const
{
    loadVector3(m_LocationBorderColor, borderColor);
    loadFloat(m_LocationBorderWidth, borderWidth);
}