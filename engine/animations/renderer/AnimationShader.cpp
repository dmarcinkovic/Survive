//
// Created by david on 12. 08. 2020..
//

#include <string>

#include "AnimationShader.h"

Survive::AnimationShader::AnimationShader()
		: Shader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	loadUniformLocations();
}

void Survive::AnimationShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::AnimationShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void Survive::AnimationShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::AnimationShader::loadUniformLocations()
{
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");

	m_LocationLightColor = glGetUniformLocation(m_Program, "lightColor");
	m_LocationLightPosition = glGetUniformLocation(m_Program, "lightPosition");

	for (int i = 0; i < MAX_JOINTS; ++i)
	{
		std::string name = "jointTransforms[" + std::to_string(i) + "]";
		m_LocationJointTransforms[i] = glGetUniformLocation(m_Program, name.c_str());
	}

	m_LocationPlane = glGetUniformLocation(m_Program, "plane");
	m_LocationCameraPosition = glGetUniformLocation(m_Program, "cameraPosition");

	m_LocationLightProjectionMatrix = glGetUniformLocation(m_Program, "lightProjectionMatrix");
	m_LocationLightViewMatrix = glGetUniformLocation(m_Program, "lightViewMatrix");

	m_LocationObjectTexture = glGetUniformLocation(m_Program, "objectTexture");
	m_LocationSkybox = glGetUniformLocation(m_Program, "skybox");
	m_LocationBloomTexture = glGetUniformLocation(m_Program, "bloomTexture");
	m_LocationShadowMap = glGetUniformLocation(m_Program, "shadowMap");

	m_LocationReflectiveFactor = glGetUniformLocation(m_Program, "reflectiveFactor");
	m_LocationRefractionFactor = glGetUniformLocation(m_Program, "refractionFactor");
	m_LocationRefractionIndex = glGetUniformLocation(m_Program, "refractionIndex");

	m_LocationAddShadow = glGetUniformLocation(m_Program, "addShadow");
	m_LocationAddBloom = glGetUniformLocation(m_Program, "addBloom");
	m_LocationBloomStrength = glGetUniformLocation(m_Program, "bloomStrength");

	m_LocationColor = glGetUniformLocation(m_Program, "color");
	m_LocationRenderColor = glGetUniformLocation(m_Program, "renderColor");

	m_LocationShineDamper = glGetUniformLocation(m_Program, "shineDamper");
	m_LocationMaterial = glGetUniformLocation(m_Program, "material");
}

void Survive::AnimationShader::loadLight(const glm::vec3 &lightPosition, const glm::vec3 &lightColor,
										 float shineDamper, int material) const
{
	loadVector3(m_LocationLightPosition, lightPosition);
	loadVector3(m_LocationLightColor, lightColor);

	loadFloat(m_LocationShineDamper, shineDamper);
	loadInteger(m_LocationMaterial, material);
}

void Survive::AnimationShader::loadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const
{
	for (int i = 0; i < jointTransforms.size(); ++i)
	{
		loadMatrix(m_LocationJointTransforms[i], jointTransforms[i]);
	}
	
	for (auto i = jointTransforms.size(); i < MAX_JOINTS; ++i)
	{
		loadMatrix(m_LocationJointTransforms[i], glm::mat4{});
	}
}

void Survive::AnimationShader::loadPlane(const glm::vec4 &plane) const
{
	loadVector4(m_LocationPlane, plane);
}

void Survive::AnimationShader::loadColor(const glm::vec4 &color) const
{
	loadInteger(m_LocationRenderColor, 1);
	loadVector4(m_LocationColor, color);
}

void Survive::AnimationShader::loadBloom(bool loadBloom) const
{
	loadInteger(m_LocationAddBloom, loadBloom);
}

void Survive::AnimationShader::loadBloomTexture(float bloomStrength) const
{
	loadInteger(m_LocationBloomTexture, 3);
	loadFloat(m_LocationBloomStrength, bloomStrength);
}

void Survive::AnimationShader::loadAddShadow(bool addShadow) const
{
	loadInteger(m_LocationAddShadow, addShadow);
}

void Survive::AnimationShader::loadRefractionData(float refractionIndex, float refractionFactor) const
{
	loadFloat(m_LocationRefractionIndex, refractionIndex);
	loadFloat(m_LocationRefractionFactor, refractionFactor);
}

void Survive::AnimationShader::loadReflectionFactor(float reflectionFactor) const
{
	loadFloat(m_LocationReflectiveFactor, reflectionFactor);
}

void Survive::AnimationShader::loadTextures() const
{
	loadInteger(m_LocationObjectTexture, 0);
	loadInteger(m_LocationShadowMap, 1);
	loadInteger(m_LocationSkybox, 2);

	loadInteger(m_LocationRenderColor, 0);
}

void Survive::AnimationShader::loadLightViewMatrix(const glm::mat4 &lightViewMatrix) const
{
	loadMatrix(m_LocationLightViewMatrix, lightViewMatrix);
}

void Survive::AnimationShader::loadLightProjectionMatrix(const glm::mat4 &lightProjectionMatrix) const
{
	loadMatrix(m_LocationLightProjectionMatrix, lightProjectionMatrix);
}

void Survive::AnimationShader::loadCameraPosition(const glm::vec3 &cameraPosition) const
{
	loadVector3(m_LocationCameraPosition, cameraPosition);
}
