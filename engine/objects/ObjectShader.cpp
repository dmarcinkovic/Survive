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

    m_LocationLightColor = glGetUniformLocation(m_Program, "lightColor");
    m_LocationLightPos = glGetUniformLocation(m_Program, "lightPosition");
    m_LocationLightViewMatrix = glGetUniformLocation(m_Program, "lightViewMatrix");
    m_LocationLightProjection = glGetUniformLocation(m_Program, "lightProjectionMatrix");
}

void ObjectShader::loadLight(const glm::vec3 &lightPos, const glm::vec3 &lightColor) const
{
    loadVector3(m_LocationLightPos, lightPos);
    loadVector3(m_LocationLightColor, lightColor);
}

void ObjectShader::loadLightProjection(const glm::mat4 &lightProjection) const
{
    loadMatrix(m_LocationLightProjection, lightProjection);
}

void ObjectShader::loadLightViewMatrix(const glm::mat4 &viewMatrix) const
{
    loadMatrix(m_LocationLightViewMatrix, viewMatrix);
}
