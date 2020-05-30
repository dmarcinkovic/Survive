//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXTSHADER_H
#define SURVIVE_TEXTSHADER_H


#include "../shader/Shader.h"

class TextShader : public Shader
{
private:
    constexpr static const char* VERTEX_FILE = "engine/shader/sources/TextVertexShader.glsl";
    constexpr static const char* FRAGMENT_FILE = "engine/shader/sources/TextFragmentShader.glsl";

    GLuint m_LocationColor{};
    GLuint m_LocationBorderWidth{};
    GLuint m_LocationBorderColor{};

    GLuint m_LocationTransformationMatrix{};

public:
    TextShader();

    void loadColor(const glm::vec3 &color) const;

    void loadBorder(const glm::vec3 &borderColor, float borderWidth) const;

    void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

private:
    void getUniformLocations();
};


#endif //SURVIVE_TEXTSHADER_H
