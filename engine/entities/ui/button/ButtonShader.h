//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_BUTTONSHADER_H
#define SURVIVE_BUTTONSHADER_H

#include "Shader.h"

namespace Survive
{
	class ButtonShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "ButtonVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "ButtonFragmentShader.glsl"
		;

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationColor{};
		GLint m_LocationIsLoadingImage{};

	public:
		ButtonShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadColor(const glm::vec4 &color) const;

		void loadIsLoadingImage(bool value) const;

	private:
		void getUniformLocations();
	};
}


#endif //SURVIVE_BUTTONSHADER_H
