//
// Created by david on 12. 08. 2020..
//

#include "AnimationShader.h"

AnimationShader::AnimationShader()
        : Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
    loadUniformLocations();
}

void AnimationShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
    loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void AnimationShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
    loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void AnimationShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
    loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void AnimationShader::loadUniformLocations()
{
    m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
    m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
    m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");

    m_LocationLightColor = glGetUniformLocation(m_Program, "lightColor");
    m_LocationLightPosition = glGetUniformLocation(m_Program, "lightPosition");
}

void AnimationShader::loadLight(const glm::vec3 &lightPosition, const glm::vec3 &lightColor) const
{
    loadVector3(m_LocationLightPosition, lightPosition);
    loadVector3(m_LocationLightColor, lightColor);
}
