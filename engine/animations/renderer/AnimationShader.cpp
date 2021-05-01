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
}

void Survive::AnimationShader::loadLight(const glm::vec3 &lightPosition, const glm::vec3 &lightColor) const
{
	loadVector3(m_LocationLightPosition, lightPosition);
	loadVector3(m_LocationLightColor, lightColor);
}

void Survive::AnimationShader::loadJointTransforms(const std::vector<JointTransform> &jointTransforms) const
{
	for (int i = 0; i < jointTransforms.size(); ++i)
	{
		loadMatrix(m_LocationJointTransforms[i], jointTransforms[i].getLocalTransform());
	}

	for (int i = jointTransforms.size(); i < MAX_JOINTS; ++i)
	{
		glm::mat4 emptyMatrix{};
		loadMatrix(m_LocationJointTransforms[i], emptyMatrix);
	}
}

void Survive::AnimationShader::loadPlane(const glm::vec4 &plane) const
{
	loadVector4(m_LocationPlane, plane);
}
