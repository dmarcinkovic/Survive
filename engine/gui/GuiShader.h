//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUISHADER_H
#define SURVIVE_GUISHADER_H

#include <glm/glm.hpp>

#include "../shader/Shader.h"

class GuiShader : public Shader
{
private:
	constexpr static const char *VERTEX_FILE = "engine/shader/sources/GuiVertexShader.glsl";
	constexpr static const char *FRAGMENT_FILE = "engine/shader/sources/GuiFragmentShader.glsl";

	GLuint m_LocationTransformationMatrix{};
	GLuint m_LocationProjectionMatrix{};

public:
	GuiShader();

	void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

	void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

private:
	void getUniformLocations();
};


#endif //SURVIVE_GUISHADER_H
