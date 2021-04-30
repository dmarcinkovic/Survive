//
// Created by david on 22. 02. 2021..
//

#include "WaterShader.h"

Survive::WaterShader::WaterShader()
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
	m_LocationDepthMap = glGetUniformLocation(m_Program, "depthMap");

	m_LocationDuDvMap = glGetUniformLocation(m_Program, "duDvMap");
	m_LocationNormalMap = glGetUniformLocation(m_Program, "normalMap");

	m_LocationMoveFactor = glGetUniformLocation(m_Program, "moveFactor");

	m_LocationCameraPosition = glGetUniformLocation(m_Program, "cameraPosition");
	m_LocationLightColor = glGetUniformLocation(m_Program, "lightColor");
	m_LocationLightPosition = glGetUniformLocation(m_Program, "lightPosition");

	m_LocationNear = glGetUniformLocation(m_Program, "near");
	m_LocationFar = glGetUniformLocation(m_Program, "far");
}

void WaterShader::loadTextures() const
{
	loadInteger(m_LocationReflectionTexture, 0);
	loadInteger(m_LocationRefractionTexture, 1);
	loadInteger(m_LocationDuDvMap, 2);
	loadInteger(m_LocationNormalMap, 3);
	loadInteger(m_LocationDepthMap, 4);
}

void WaterShader::loadMoveFactor(float moveFactor) const
{
	loadFloat(m_LocationMoveFactor, moveFactor);
}

void Survive::WaterShader::loadCameraPosition(const glm::vec3 &cameraPosition) const
{
	loadVector3(m_LocationCameraPosition, cameraPosition);
}

void Survive::WaterShader::loadLight(const Light &light) const
{
	loadVector3(m_LocationLightColor, light.color());
	loadVector3(m_LocationLightPosition, light.position());
}

void Survive::WaterShader::loadNearAndFar(float near, float far) const
{
	loadFloat(m_LocationNear, near);
	loadFloat(m_LocationFar, far);
}
