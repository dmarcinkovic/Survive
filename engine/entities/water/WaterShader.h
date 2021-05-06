//
// Created by david on 22. 02. 2021..
//

#ifndef SURVIVE_WATERSHADER_H
#define SURVIVE_WATERSHADER_H


#include "../../core/shader/Shader.h"
#include "../../scene/light/Light.h"

namespace Survive
{
	class WaterShader : public Shader
	{
	private:
		static constexpr const char *VERTEX_SHADER = "engine/core/shader/sources/WaterVertexShader.glsl";
		static constexpr const char *FRAGMENT_SHADER = "engine/core/shader/sources/WaterFragmentShader.glsl";

		GLuint m_LocationTransformationMatrix{};
		GLuint m_LocationViewMatrix{};
		GLuint m_LocationProjectionMatrix{};

		GLuint m_LocationReflectionTexture{};
		GLuint m_LocationRefractionTexture{};
		GLuint m_LocationDepthMap{};

		GLuint m_LocationDuDvMap{};
		GLuint m_LocationNormalMap{};
		GLuint m_LocationMoveFactor{};

		GLuint m_LocationCameraPosition{};
		GLuint m_LocationLightColor{};
		GLuint m_LocationLightPosition{};

		GLuint m_LocationNear{};
		GLuint m_LocationFar{};

	public:
		WaterShader();

		void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

		void loadViewMatrix(const glm::mat4 &viewMatrix) const;

		void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

		void loadTextures() const;

		void loadMoveFactor(float moveFactor) const;

		void loadCameraPosition(const glm::vec3 &cameraPosition) const;

		void loadLight(const Light &light) const;

		void loadNearAndFar(float near, float far) const;

	private:
		void loadUniformLocations();
	};
}

#endif //SURVIVE_WATERSHADER_H
