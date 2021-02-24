//
// Created by david on 22. 02. 2021..
//

#include "WaterShader.h"

WaterShader::WaterShader()
	: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	loadUniformLocations();
}

void WaterShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void WaterShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void WaterShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void WaterShader::loadUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");

	m_LocationReflectionTexture = glGetUniformLocation(m_Program, "reflectionTexture");
	m_LocationRefractionTexture = glGetUniformLocation(m_Program, "refractionTexture");

	m_LocationDuDvMap = glGetUniformLocation(m_Program, "duDvMap");
	m_LocationNormalMap = glGetUniformLocation(m_Program, "normalMap");

	m_LocationMoveFactor = glGetUniformLocation(m_Program, "moveFactor");

	m_LocationCameraPosition = glGetUniformLocation(m_Program, "cameraPosition");
}

void WaterShader::loadTextures() const
{
	loadInteger(m_LocationReflectionTexture, 0);
	loadInteger(m_LocationRefractionTexture, 1);
	loadInteger(m_LocationDuDvMap, 2);
	loadInteger(m_LocationNormalMap, 3);
}

void WaterShader::loadMoveFactor(float moveFactor) const
{
	loadFloat(m_LocationMoveFactor, moveFactor);
}

void WaterShader::loadCameraPosition(const glm::vec3 &cameraPosition) const
{
	loadVector3(m_LocationCameraPosition, cameraPosition);
}
