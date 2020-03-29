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

public:
    TextShader();
};


#endif //SURVIVE_TEXTSHADER_H
