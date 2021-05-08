//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAINSHADER_H
#define SURVIVE_TERRAINSHADER_H

#include "Shader.h"
#include "Light.h"

namespace Survive
{
	class TerrainShader : public Shader
	{
	private:
		constexpr static const char *VERTEX_FILE = "engine/core/shader/sources/TerrainVertexShader.glsl";
		constexpr static const char *FRAGMENT_FILE = "engine/core/shader/sources/TerrainFragmentShader.glsl";

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationProjectionMatrix{};
		GLint m_LocationViewMatrix{};

		GLint m_LocationLightProjection{};
		GLint m_LocationLightView{};

		GLint m_LocationLightPosition{};
		GLint m_LocationLightColor{};

		GLint m_LocationShadowMap{};
		GLint m_LocationBlendMap{};
		GLint m_LocationGrass{};
		GLint m_LocationDirt{};
		GLint m_LocationRock{};
		GLint m_LocationFlowers{};

		GLint m_LocationPlane{};
		GLint m_LocationAddShadow{};

	public:
		TerrainShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadLightProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadLightViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadTextures() const;

		void loadLight(const Light &light) const;

		void loadPlane(const glm::vec4 &plane) const;

		void loadAddShadow(int addShadow) const;

	private:
		void getUniformLocations();
	};
}

#endif //SURVIVE_TERRAINSHADER_H
