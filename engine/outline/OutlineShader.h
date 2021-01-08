//
// Created by david on 27. 12. 2020..
//

#ifndef SURVIVE_OUTLINESHADER_H
#define SURVIVE_OUTLINESHADER_H


#include "../shader/Shader.h"

class OutlineShader : public Shader
{
private:
	constexpr static const char *VERTEX_SHADER = "engine/shader/sources/OutlineVertexShader.glsl";
	constexpr static const char *FRAGMENT_SHADER = "engine/shader/sources/OutlineFragmentShader.glsl";

	GLuint m_LocationTransformationMatrix{};
	GLuint m_LocationProjectionMatrix{};
	GLuint m_LocationViewMatrix{};

public:
	OutlineShader();

	void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

	void loadViewMatrix(const glm::mat4 &viewMatrix) const;

	void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

private:
	void loadUniformLocations();
};


#endif //SURVIVE_OUTLINESHADER_H