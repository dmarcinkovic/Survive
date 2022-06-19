//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_SHADOWSHADER_H
#define SURVIVE_SHADOWSHADER_H

#include <vector>

#include "Shader.h"

namespace Survive
{
	class ShadowShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "ShadowVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "ShadowFragmentShader.glsl"
		;
		static constexpr int MAX_JOINTS = 50;

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationViewMatrix{};
		GLint m_LocationProjectionMatrix{};

		GLint m_LocationJointTransforms[MAX_JOINTS]{};
		GLint m_LocationLoadAnimatedModel{};

	public:
		ShadowShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadAnimatedModel(bool loadAnimatedModel) const;

		void loadJointTransforms(const std::vector<glm::mat4> &jointTransforms) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_SHADOWSHADER_H
