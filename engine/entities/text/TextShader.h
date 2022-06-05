//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXTSHADER_H
#define SURVIVE_TEXTSHADER_H

#include "Shader.h"

namespace Survive
{
	class TextShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "TextVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "TextFragmentShader.glsl"
		;

		GLint m_LocationColor{};
		GLint m_LocationBorderWidth{};
		GLint m_LocationBorderColor{};

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationProjectionMatrix{};

	public:
		TextShader();

		void loadColor(const glm::vec3 &color) const;

		void loadBorder(const glm::vec3 &borderColor, float borderWidth) const;

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_TEXTSHADER_H
