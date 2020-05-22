//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAINSHADER_H
#define SURVIVE_TERRAINSHADER_H


#include "../shader/Shader.h"

class TerrainShader : public Shader
{
private:
    constexpr static const char *VERTEX_FILE = "engine/shader/sources/TerrainVertexShader.glsl";
    constexpr static const char* FRAGMENT_FILE = "engine/shader/sources/TerrainFragmentShader.glsl";

public:
    TerrainShader();


};


#endif //SURVIVE_TERRAINSHADER_H
