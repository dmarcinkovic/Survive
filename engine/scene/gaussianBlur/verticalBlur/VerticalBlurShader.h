//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_VERTICALBLURSHADER_H
#define SURVIVE_VERTICALBLURSHADER_H


#include "Shader.h"

namespace Survive
{
	class VerticalBlurShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "VerticalBlurVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "BlurFragmentShader.glsl"
		;

		GLint m_LocationTargetHeight{};

	public:
		VerticalBlurShader();

		void loadTargetHeight(float targetHeight) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_VERTICALBLURSHADER_H
