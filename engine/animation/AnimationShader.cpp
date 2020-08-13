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

void AnimationShader::loadLight(const glm::vec3 &lightPosition, const glm::vec3 &lightColor) const
{
    loadVector3(m_LocationLightPosition, lightPosition);
    loadVector3(m_LocationLightColor, lightColor);
}

void AnimationShader::loadUniformLocations()
{
    m_LocationTransformationMatrix = glGetAttribLocation(m_Program, "transformationMatrix");
    m_LocationViewMatrix = glGetAttribLocation(m_Program, "viewMatrix");
    m_LocationProjectionMatrix = glGetAttribLocation(m_Program, "projectionMatrix");

    m_LocationLightColor = glGetAttribLocation(m_Program, "lightColor");
    m_LocationLightPosition = glGetAttribLocation(m_Program, "lightPosition");
}
