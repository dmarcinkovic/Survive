//
// Created by david on 22. 02. 2021..
//

#ifndef SURVIVE_WATERSHADER_H
#define SURVIVE_WATERSHADER_H


#include "../shader/Shader.h"

class WaterShader : public Shader
{
private:
	static constexpr const char* VERTEX_SHADER = "engine/shader/sources/WaterVertexShader.glsl";
	static constexpr const char* FRAGMENT_SHADER = "engine/shader/sources/WaterFragmentShader.glsl";

	GLuint m_LocationTransformationMatrix{};
	GLuint m_LocationViewMatrix{};
	GLuint m_LocationProjectionMatrix{};

	GLuint m_LocationReflectionTexture{};
	GLuint m_LocationRefractionTexture{};

	GLuint m_LocationDuDvMap;
	GLuint m_LocationNormalMap;

public:
	WaterShader();

	void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

	void loadViewMatrix(const glm::mat4 &viewMatrix) const;

	void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

	void loadTextures() const;

private:
	void loadUniformLocations();
};


#endif //SURVIVE_WATERSHADER_H
