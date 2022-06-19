//
// Created by david on 24. 01. 2022..
//

#ifndef SURVIVE_WIREFRAMESHADER_H
#define SURVIVE_WIREFRAMESHADER_H

#include "Shader.h"

namespace Survive
{
	class WireframeShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "WireVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "WireFragmentShader.glsl"
		;

	public:
		WireframeShader();
	};
}

#endif //SURVIVE_WIREFRAMESHADER_H
