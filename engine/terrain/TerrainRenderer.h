//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAINRENDERER_H
#define SURVIVE_TERRAINRENDERER_H

#include "TerrainShader.h"
#include "Terrain.h"
#include "../camera/Camera.h"
#include "../light/Light.h"

class TerrainRenderer
{
private:
    constexpr static const float fieldOfView = 70.0f;

    TerrainShader m_Shader;
    Terrain m_Terrain{};

public:
    TerrainRenderer();

    void render(const Camera &camera, const Light &light, GLuint shadowMap) const;

    void addTerrain(Terrain &terrain);

private:
    void prepareRendering() const;

    void finishRendering() const;
};


#endif //SURVIVE_TERRAINRENDERER_H
