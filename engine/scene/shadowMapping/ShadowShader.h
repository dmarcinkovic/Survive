//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_SHADOWSHADER_H
#define SURVIVE_SHADOWSHADER_H

#include "Shader.h"

namespace Survive
{
	class ShadowShader : public Shader
	{
	private:
		static constexpr const char *VERTEX_SHADER = "engine/core/shader/sources/ShadowVertexShader.glsl";
		static constexpr const char *FRAGMENT_SHADER = "engine/core/shader/sources/ShadowFragmentShader.glsl";

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationViewMatrix{};
		GLint m_LocationProjectionMatrix{};

	public:
		ShadowShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_SHADOWSHADER_H
