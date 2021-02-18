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

	m_LocationBlendMap = glGetUniformLocation(m_Program, "blendMap");

	m_LocationRock = glGetUniformLocation(m_Program, "rock");
	m_LocationGrass = glGetUniformLocation(m_Program, "grass");
	m_LocationDirt = glGetUniformLocation(m_Program, "dirt");
	m_LocationFlowers = glGetUniformLocation(m_Program, "flowers");

	m_LocationShadowMap = glGetUniformLocation(m_Program, "shadowMap");

	m_LocationLightColor = glGetUniformLocation(m_Program, "lightColor");
	m_LocationCameraPosition = glGetUniformLocation(m_Program, "cameraPosition");
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

void TerrainShader::loadTextures() const
{
	loadInteger(m_LocationShadowMap, 0);
	loadInteger(m_LocationBlendMap, 1);
	loadInteger(m_LocationDirt, 2);
	loadInteger(m_LocationGrass, 3);
	loadInteger(m_LocationRock, 4);
	loadInteger(m_LocationFlowers, 5);
}

void TerrainShader::loadLightColor(const glm::vec3 &lightColor) const
{
	loadVector3(m_LocationLightColor, lightColor);
}

void TerrainShader::loadCameraPosition(const glm::vec3 &cameraPosition) const
{
	loadVector3(m_LocationCameraPosition, cameraPosition);
}
