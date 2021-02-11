//
// Created by david on 05. 02. 2021..
//

#ifndef SURVIVE_PARTICLESHADER_H
#define SURVIVE_PARTICLESHADER_H


#include "../shader/Shader.h"

class ParticleShader : public Shader
{
private:
	static constexpr const char *VERTEX_SHADER = "engine/shader/sources/ParticleVertexShader.glsl";
	static constexpr const char  *FRAGMENT_SHADER = "engine/shader/sources/ParticleFragmentShader.glsl";

	GLuint m_LocationNumberOfRows{};
	GLuint m_LocationProjectionMatrix{};

public:
	ParticleShader();

	void loadNumberOfRows(int rows) const;

	void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

private:
	void getUniformLocations();
};


#endif //SURVIVE_PARTICLESHADER_H
