//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_HORIZONTALBLURSHADER_H
#define SURVIVE_HORIZONTALBLURSHADER_H


#include "../../core/shader/Shader.h"

namespace Survive
{
	class HorizontalBlurShader : public Shader
	{
	private:
		static constexpr const char *VERTEX_SHADER = "engine/shader/sources/HorizontalBlurVertexShader.glsl";
		static constexpr const char *FRAGMENT_SHADER = "engine/shader/sources/BlurFragmentShader.glsl";

		GLuint m_LocationTargetWidth{};

	public:
		HorizontalBlurShader();

		void loadTargetWidth(float targetWidth) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_HORIZONTALBLURSHADER_H
