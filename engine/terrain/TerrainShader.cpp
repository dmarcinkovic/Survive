//
// Created by david on 22. 05. 2020..
//

#include "TerrainShader.h"

TerrainShader::TerrainShader()
        : Shader(VERTEX_FILE, FRAGMENT_FILE)
{
    getUniformLocations();
}

void TerrainShader::getUniformLocations()
{
    m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
    m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
    m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
    m_LocationLightProjection = glGetUniformLocation(m_Program, "lightProjectionMatrix");
    m_LocationLightView = glGetUniformLocation(m_Program, "lightViewMatrix");
}

void TerrainShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
    loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void TerrainShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
    loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void TerrainShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
    loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void TerrainShader::loadLightProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
    loadMatrix(m_LocationLightProjection, projectionMatrix);
}

void TerrainShader::loadLightViewMatrix(const glm::mat4 &viewMatrix) const
{
    loadMatrix(m_LocationLightView, viewMatrix);
}
