//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_VERTICALBLURSHADER_H
#define SURVIVE_VERTICALBLURSHADER_H


#include "../../shader/Shader.h"

namespace Survive
{
	class VerticalBlurShader : public Shader
	{
	private:
		static constexpr const char *VERTEX_SHADER = "engine/shader/sources/VerticalBlurVertexShader.glsl";
		static constexpr const char *FRAGMENT_SHADER = "engine/shader/sources/BlurFragmentShader.glsl";

		GLuint m_LocationTargetHeight{};

	public:
		VerticalBlurShader();

		void loadTargetHeight(float targetHeight) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_VERTICALBLURSHADER_H
