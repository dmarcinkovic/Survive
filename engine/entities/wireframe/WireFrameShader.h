//
// Created by david on 24. 01. 2022..
//

#ifndef SURVIVE_WIREFRAMESHADER_H
#define SURVIVE_WIREFRAMESHADER_H

#include "Shader.h"

namespace Survive
{
	class WireFrameShader : public Shader
	{
	private:
		static constexpr const char *VERTEX_SHADER = "engine/core/shader/sources/WireVertexShader.glsl";
		static constexpr const char *FRAGMENT_SHADER = "engine/core/shader/sources/WireFragmentShader.glsl";

	public:
		WireFrameShader();
	};
}

#endif //SURVIVE_WIREFRAMESHADER_H
