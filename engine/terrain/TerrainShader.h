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

    GLuint m_LocationTransformationMatrix{};
    GLuint m_LocationProjectionMatrix{};
    GLuint m_LocationViewMatrix{};

public:
    TerrainShader();

    void loadTransformationMatrix(const glm::mat4 &transformationMatrix) const;

    void loadProjectionMatrix(const glm::mat4 &projectionMatrix) const;

    void loadViewMatrix(const glm::mat4 &viewMatrix) const;

private:
    void getUniformLocations();
};


#endif //SURVIVE_TERRAINSHADER_H
