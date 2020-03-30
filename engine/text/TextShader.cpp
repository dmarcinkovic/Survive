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
}

void TextShader::loadColor(const glm::vec3 &color) const
{
    loadVector3(m_LocationColor, color);
}
