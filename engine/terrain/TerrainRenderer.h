//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_TERRAINRENDERER_H
#define SURVIVE_TERRAINRENDERER_H

#include "TerrainShader.h"
#include "Terrain.h"
#include "../camera/Camera.h"

class TerrainRenderer
{
private:
    constexpr static const float fieldOfView = 70.0f;
    constexpr static const float near = 0.1f;
    constexpr static const float far = 1000.0f;

    TerrainShader m_Shader;
    Terrain *m_Terrain{};

    std::vector<Texture> m_Textures;

public:
    TerrainRenderer();

    void render(const Camera &camera) const;

    void addTerrain(Terrain &terrain);

private:
    void prepareRendering() const;

    static void finishRendering();
};


#endif //SURVIVE_TERRAINRENDERER_H
