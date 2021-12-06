//
// Created by david on 12. 08. 2020..
//

#include <string>

#include "AnimationShader.h"

Survive::AnimationShader::AnimationShader()
		: ObjectShader(VERTEX_SHADER, FRAGMENT_SHADER)
{
	loadUniformLocations();
}

void Survive::AnimationShader::loadUniformLocations()
{
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");

	m_LocationLightColor = glGetUniformLocation(m_Program, "lightColor");
	m_LocationLightPos = glGetUniformLocation(m_Program, "lightPosition");

	for (int i = 0; i < MAX_JOINTS; ++i)
	{
		std::string name = "jointTransforms[" + std::to_string(i) + "]";
		m_LocationJointTransforms[i] = glGetUniformLocation(m_Program, name.c_str());
	}

	m_LocationPlane = glGetUniformLocation(m_Program, "plane");
	m_LocationCameraPosition = glGetUniformLocation(m_Program, "cameraPosition");

	m_LocationLightProjection = glGetUniformLocation(m_Program, "lightProjectionMatrix");
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

	m_LocationShineDamper = glGetUniformLocation(m_Program, "shineDamper");
	m_LocationMaterial = glGetUniformLocation(m_Program, "material");
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
