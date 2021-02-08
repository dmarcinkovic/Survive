//
// Created by david on 12. 01. 2021..
//

#ifndef SURVIVE_MOUSEPICKINGSHADER_H
#define SURVIVE_MOUSEPICKINGSHADER_H


#include "../shader/Shader.h"

class MousePickingShader : public Shader
{
private:
	static constexpr const char *VERTEX_SHADER = "engine/shader/sources/MousePickingVertexShader.glsl";
	static constexpr const char *FRAGMENT_SHADER = "engine/shader/sources/MousePickingFragmentShader.glsl";

	GLuint m_LocationTransformationMatrix{};
	GLuint m_LocationViewMatrix{};
	GLuint m_LocationProjectionMatrix{};
	GLuint m_LocationPickingColor{};

public:
	MousePickingShader();

	void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

	void loadViewMatrix(const glm::mat4 &viewMatrix) const;

	void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

	void loadPickingColor(const glm::vec4 &pickingColor) const;

private:
	void getUniformLocations();
};


#endif //SURVIVE_MOUSEPICKINGSHADER_H
