//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXTSHADER_H
#define SURVIVE_TEXTSHADER_H


#include "../../core/shader/Shader.h"

namespace Survive
{
	class TextShader : public Shader
	{
	private:
		constexpr static const char *VERTEX_FILE = "engine/core/shader/sources/TextVertexShader.glsl";
		constexpr static const char *FRAGMENT_FILE = "engine/core/shader/sources/TextFragmentShader.glsl";

		GLint m_LocationColor{};
		GLint m_LocationBorderWidth{};
		GLint m_LocationBorderColor{};

		GLint m_LocationTransformationMatrix{};

	public:
		TextShader();

		void loadColor(const glm::vec3 &color) const;

		void loadBorder(const glm::vec3 &borderColor, float borderWidth) const;

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_TEXTSHADER_H
