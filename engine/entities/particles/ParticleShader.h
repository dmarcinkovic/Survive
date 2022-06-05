//
// Created by david on 05. 02. 2021..
//

#ifndef SURVIVE_PARTICLESHADER_H
#define SURVIVE_PARTICLESHADER_H

#include "Shader.h"

namespace Survive
{
	class ParticleShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "ParticleVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "ParticleFragmentShader.glsl"
		;

		GLint m_LocationNumberOfRows{};
		GLint m_LocationNumberOfCols{};
		GLint m_LocationProjectionMatrix{};

		GLint m_LocationColor{};

	public:
		ParticleShader();

		void loadDimensions(unsigned rows, unsigned cols) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadColor(const glm::vec4 &color) const;

	private:
		void getUniformLocations();
	};
}


#endif //SURVIVE_PARTICLESHADER_H
