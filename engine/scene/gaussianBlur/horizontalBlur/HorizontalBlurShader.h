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
		static constexpr const char *VERTEX_SHADER = "engine/core/shader/sources/HorizontalBlurVertexShader.glsl";
		static constexpr const char *FRAGMENT_SHADER = "engine/core/shader/sources/BlurFragmentShader.glsl";

		GLint m_LocationTargetWidth{};

	public:
		HorizontalBlurShader();

		void loadTargetWidth(float targetWidth) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_HORIZONTALBLURSHADER_H
