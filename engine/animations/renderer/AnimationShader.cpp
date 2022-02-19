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
	ObjectShader::loadUniformLocations();

	for (int i = 0; i < MAX_JOINTS; ++i)
	{
		std::string name = "jointTransforms[" + std::to_string(i) + "]";
		m_LocationJointTransforms[i] = glGetUniformLocation(m_Program, name.c_str());
	}
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
