//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_BUTTONSHADER_H
#define SURVIVE_BUTTONSHADER_H


#include "../../../core/shader/Shader.h"

namespace Survive
{
	class ButtonShader : public Shader
	{
	private:
		constexpr static const char *VERTEX_FILE = "engine/core/shader/sources/ButtonVertexShader.glsl";
		constexpr static const char *FRAGMENT_FILE = "engine/core/shader/sources/ButtonFragmentShader.glsl";

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
