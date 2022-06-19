//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUISHADER_H
#define SURVIVE_GUISHADER_H

#include <glm/glm.hpp>

#include "Shader.h"

namespace Survive
{
	class GuiShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "GuiVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "GuiFragmentShader.glsl"
		;

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationProjectionMatrix{};
		GLint m_LocationColor{};

	public:
		GuiShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadColor(const glm::vec4 &color) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_GUISHADER_H
