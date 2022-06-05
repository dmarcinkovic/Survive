//
// Created by david on 22. 05. 2020..
//

#include "TerrainShader.h"

Survive::TerrainShader::TerrainShader()
		: Shader(vertexShaderSource, fragmentShaderSource)
{
	getUniformLocations();
}

void Survive::TerrainShader::getUniformLocations()
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
	m_LocationLightPosition = glGetUniformLocation(m_Program, "lightPosition");

	m_LocationPlane = glGetUniformLocation(m_Program, "plane");
	m_LocationAddShadow = glGetUniformLocation(m_Program, "addShadow");
}

void Survive::TerrainShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::TerrainShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::TerrainShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void Survive::TerrainShader::loadLightProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationLightProjection, projectionMatrix);
}

void Survive::TerrainShader::loadLightViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationLightView, viewMatrix);
}

void Survive::TerrainShader::loadTextures() const
{
	loadInteger(m_LocationBlendMap, 0);
	loadInteger(m_LocationDirt, 1);
	loadInteger(m_LocationGrass, 2);
	loadInteger(m_LocationRock, 3);
	loadInteger(m_LocationFlowers, 4);
	loadInteger(m_LocationShadowMap, 5);
}

void Survive::TerrainShader::loadLight(const Light &light) const
{
	loadVector3(m_LocationLightColor, light.color());
	loadVector3(m_LocationLightPosition, light.position());
}

void Survive::TerrainShader::loadPlane(const glm::vec4 &plane) const
{
	loadVector4(m_LocationPlane, plane);
}

void Survive::TerrainShader::loadAddShadow(int addShadow) const
{
	loadInteger(m_LocationAddShadow, addShadow);
}

