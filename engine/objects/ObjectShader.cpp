//
// Created by david on 17. 05. 2020..
//

#include "ObjectShader.h"

ObjectShader::ObjectShader()
    : Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
    loadUniformLocations();
}

void ObjectShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
    loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void ObjectShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
    loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void ObjectShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
    loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void ObjectShader::loadUniformLocations()
{
    m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
    m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
    m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
}
