//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_BUTTONSHADER_H
#define SURVIVE_BUTTONSHADER_H


#include "../../shader/Shader.h"

class ButtonShader : public Shader
{
private:
    constexpr static const char *VERTEX_FILE = "engine/shader/sources/ButtonVertexShader.glsl";
    constexpr static const char *FRAGMENT_FILE = "engine/shader/sources/ButtonFragmentShader.glsl";

public:
    ButtonShader();
};


#endif //SURVIVE_BUTTONSHADER_H
