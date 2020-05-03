//
// Created by david on 03. 05. 2020..
//

#include "ButtonShader.h"

ButtonShader::ButtonShader()
        : Shader(VERTEX_FILE, FRAGMENT_FILE)
{
    getUniformLocations();
}

void ButtonShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
    loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void ButtonShader::getUniformLocations()
{
    m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
}
