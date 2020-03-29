//
// Created by david on 29. 03. 2020..
//

#include "SpritesShader.h"

SpritesShader::SpritesShader()
        : Shader(VERTEX_FILE, FRAGMENT_FILE)
{
    getUniformLocations();
}

void SpritesShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
    loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void SpritesShader::getUniformLocations()
{
    m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
}
