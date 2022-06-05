//
// Created by david on 25. 12. 2020..
//

#ifndef SURVIVE_SKYSHADER_H
#define SURVIVE_SKYSHADER_H

#include "Shader.h"

namespace Survive
{
	class SkyShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "SkyVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "SkyFragmentShader.glsl"
		;

		GLint m_LocationProjectionMatrix{};
		GLint m_LocationViewMatrix{};
		GLint m_LocationTransformationMatrix{};

		GLint m_LocationPlane{};

	public:
		SkyShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadViewAndProjectionMatrices(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix) const;

		void loadPlane(const glm::vec4 &plane) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_SKYSHADER_H
