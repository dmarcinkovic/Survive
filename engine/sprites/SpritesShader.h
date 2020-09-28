//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESSHADER_H
#define SURVIVE_SPRITESSHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../shader/Shader.h"

class SpritesShader  : public Shader
{
private:
    constexpr static const char *VERTEX_FILE = "engine/shader/sources/SpriteVertexShader.glsl";
    constexpr static const char *FRAGMENT_FILE = "engine/shader/sources/SpriteFragmentShader.glsl";

    GLuint m_LocationTransformationMatrix{};
    GLuint m_LocationRow{};
    GLuint m_LocationCol{};
    GLuint m_LocationSpriteIndex{};

public:
    SpritesShader();

    void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

    void loadSpriteSize(int row, int col) const;

    void loadSpritePosition(int currentIndex) const;

private:
    void getUniformLocations();
};


#endif //SURVIVE_SPRITESSHADER_H
