//
// Created by david on 28. 03. 2020..
//

#include "GuiShader.h"

GuiShader::GuiShader()
        : Shader(VERTEX_FILE, FRAGMENT_FILE)
{
    getUniformLocations();
}

void GuiShader::getUniformLocations()
{
    m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
    m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
}

void GuiShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
    loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void GuiShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}
