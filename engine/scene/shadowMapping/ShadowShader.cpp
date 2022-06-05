//
// Created by david on 22. 05. 2020..
//

#include <string>

#include "ShadowShader.h"

Survive::ShadowShader::ShadowShader()
		: Shader(vertexShaderSource, fragmentShaderSource)
{
	getUniformLocations();
}

void Survive::ShadowShader::loadTransformationMatrix(const glm::mat4 &transformationMatrix) const
{
	loadMatrix(m_LocationTransformationMatrix, transformationMatrix);
}

void Survive::ShadowShader::loadProjectionMatrix(const glm::mat4 &projectionMatrix) const
{
	loadMatrix(m_LocationProjectionMatrix, projectionMatrix);
}

void Survive::ShadowShader::loadViewMatrix(const glm::mat4 &viewMatrix) const
{
	loadMatrix(m_LocationViewMatrix, viewMatrix);
}

void Survive::ShadowShader::getUniformLocations()
{
	m_LocationTransformationMatrix = glGetUniformLocation(m_Program, "transformationMatrix");
	m_LocationProjectionMatrix = glGetUniformLocation(m_Program, "projectionMatrix");
	m_LocationViewMatrix = glGetUniformLocation(m_Program, "viewMatrix");

	for (int i = 0; i < MAX_JOINTS; ++i)
	{
		std::string name = "jointTransforms[" + std::to_string(i) + "]";
		m_LocationJointTransforms[i] = glGetUniformLocation(m_Program, name.c_str());
	}

	m_LocationLoadAnimatedModel = glGetUniformLocation(m_Program, "loadAnimatedModel");
}

void Survive::ShadowShader::loadAnimatedModel(bool loadAnimatedModel) const
{
	loadInteger(m_LocationLoadAnimatedModel, loadAnimatedModel);
}

void Survive::ShadowShader::loadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const
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
