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

    m_LocationShadowMap = glGetUniformLocation(m_Program, "shadowMap");
    m_LocationObjectTexture = glGetUniformLocation(m_Program, "objectTexture");
    m_LocationShineDamper = glGetUniformLocation(m_Program, "shineDamper");
    m_LocationMaterial = glGetUniformLocation(m_Program, "material");

    m_LocationCameraPosition = glGetUniformLocation(m_Program, "cameraPosition");
    m_LocationSkybox = glGetUniformLocation(m_Program, "skybox");
}

void
ObjectShader::loadLight(const glm::vec3 &lightPos, const glm::vec3 &lightColor, float shineDamper, int material) const
{
    loadVector3(m_LocationLightPos, lightPos);
    loadVector3(m_LocationLightColor, lightColor);

    loadFloat(m_LocationShineDamper, shineDamper);
    loadInteger(m_LocationMaterial, material);
}

void ObjectShader::loadCameraPosition(const glm::vec3 &cameraPosition) const
{
    loadVector3(m_LocationCameraPosition, cameraPosition);
}

void ObjectShader::loadLightProjection(const glm::mat4 &lightProjection) const
{
    loadMatrix(m_LocationLightProjection, lightProjection);
}

void ObjectShader::loadLightViewMatrix(const glm::mat4 &viewMatrix) const
{
    loadMatrix(m_LocationLightViewMatrix, viewMatrix);
}

void ObjectShader::loadTextures() const
{
    loadInteger(m_LocationObjectTexture, 0);
    loadInteger(m_LocationShadowMap, 1);
    loadInteger(m_LocationSkybox, 2);
}
