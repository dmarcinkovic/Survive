//
// Created by david on 22. 02. 2021..
//

#ifndef SURVIVE_WATERSHADER_H
#define SURVIVE_WATERSHADER_H

#include "Shader.h"
#include "Light.h"

namespace Survive
{
	class WaterShader : public Shader
	{
	private:
		static inline const char *vertexShaderSource =
#include "WaterVertexShader.glsl"
		;
		static inline const char *fragmentShaderSource =
#include "WaterFragmentShader.glsl"
		;

		GLint m_LocationTransformationMatrix{};
		GLint m_LocationViewMatrix{};
		GLint m_LocationProjectionMatrix{};

		GLint m_LocationReflectionTexture{};
		GLint m_LocationRefractionTexture{};
		GLint m_LocationDepthMap{};

		GLint m_LocationDuDvMap{};
		GLint m_LocationNormalMap{};
		GLint m_LocationMoveFactor{};

		GLint m_LocationCameraPosition{};
		GLint m_LocationLightColor{};
		GLint m_LocationLightPosition{};

		GLint m_LocationNear{};
		GLint m_LocationFar{};

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
