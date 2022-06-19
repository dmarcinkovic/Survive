//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_HORIZONTALBLURSHADER_H
#define SURVIVE_HORIZONTALBLURSHADER_H


#include "Shader.h"

namespace Survive
{
	class HorizontalBlurShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "HorizontalBlurVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "BlurFragmentShader.glsl"
		;

		GLint m_LocationTargetWidth{};

	public:
		HorizontalBlurShader();

		void loadTargetWidth(float targetWidth) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_HORIZONTALBLURSHADER_H
