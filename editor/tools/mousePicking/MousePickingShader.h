//
// Created by david on 12. 01. 2021..
//

#ifndef SURVIVE_MOUSEPICKINGSHADER_H
#define SURVIVE_MOUSEPICKINGSHADER_H


#include "Shader.h"

namespace Survive
{
	class MousePickingShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "MousePickingVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "MousePickingFragmentShader.glsl"
		;

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationViewMatrix{};
		GLint m_LocationProjectionMatrix{};
		GLint m_LocationPickingColor{};

	public:
		MousePickingShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadPickingColor(const glm::vec4 &pickingColor) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_MOUSEPICKINGSHADER_H
