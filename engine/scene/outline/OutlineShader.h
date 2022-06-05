//
// Created by david on 27. 12. 2020..
//

#ifndef SURVIVE_OUTLINESHADER_H
#define SURVIVE_OUTLINESHADER_H

#include <glm/glm.hpp>

#include "Shader.h"

namespace Survive
{
	class OutlineShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "OutlineVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "OutlineFragmentShader.glsl"
		;

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationProjectionMatrix{};
		GLint m_LocationViewMatrix{};
		GLint m_LocationFactor{};

	public:
		OutlineShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadFactor(const glm::vec3 &factor) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_OUTLINESHADER_H
