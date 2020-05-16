//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_OBJECTSHADER_H
#define SURVIVE_OBJECTSHADER_H


#include "../shader/Shader.h"

class ObjectShader : public Shader
{
private:
    constexpr static const char* VERTEX_SHADER = "engine/shader/sources/ObjectVertexShader.glsl";
    constexpr static const char* FRAGMENT_SHADER = "engine/shader/sources/ObjectFragmentShader.glsl";

public:
    ObjectShader();

};


#endif //SURVIVE_OBJECTSHADER_H
