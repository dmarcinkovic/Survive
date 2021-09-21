//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESSHADER_H
#define SURVIVE_SPRITESSHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"

namespace Survive
{
	class SpritesShader : public Shader
	{
	private:
		constexpr static const char *VERTEX_FILE = "engine/core/shader/sources/SpriteVertexShader.glsl";
		constexpr static const char *FRAGMENT_FILE = "engine/core/shader/sources/SpriteFragmentShader.glsl";

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationRow{};
		GLint m_LocationCol{};
		GLint m_LocationSpriteIndex{};

		GLint m_LocationProjectionMatrix{};

	public:
		SpritesShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadSpriteSize(int row, int col) const;

		void loadSpritePosition(int currentIndex) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_SPRITESSHADER_H
