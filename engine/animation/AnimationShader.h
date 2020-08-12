//
// Created by david on 12. 08. 2020..
//

#ifndef SURVIVE_ANIMATIONSHADER_H
#define SURVIVE_ANIMATIONSHADER_H


#include "../shader/Shader.h"

class AnimationShader : public Shader
{
private:
    static constexpr const char* VERTEX_SHADER = "engine/shader/sources/AnimationVertexShader.glsl";
    static constexpr const char* FRAGMENT_SHADER = "engine/shader/sources/AnimationFragmentShader.glsl";

public:
    AnimationShader();


};


#endif //SURVIVE_ANIMATIONSHADER_H
