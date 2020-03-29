//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESSHADER_H
#define SURVIVE_SPRITESSHADER_H

#include <GL/glew.h>
#include <glm/detail/type_mat.hpp>

#include "../shader/Shader.h"

class SpritesShader  : public Shader
{
private:
    constexpr static const char *VERTEX_FILE = "engine/shader/sources/GuiVertexShader.glsl";
    constexpr static const char *FRAGMENT_FILE = "engine/shader/sources/GuiFragmentShader.glsl";

    GLuint m_LocationTransformationMatrix{};

public:
    SpritesShader();

    void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

private:
    void getUniformLocations();
};


#endif //SURVIVE_SPRITESSHADER_H
