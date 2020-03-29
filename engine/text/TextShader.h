//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXTSHADER_H
#define SURVIVE_TEXTSHADER_H


#include "../shader/Shader.h"

class TextShader : public Shader
{
private:
    constexpr static const char* VERTEX_FILE = "";
    constexpr static const char* FRAGMENT_FILE = "";

public:
    TextShader();
};


#endif //SURVIVE_TEXTSHADER_H
