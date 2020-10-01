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
    constexpr static const float rotationX = 90.0f;

    TerrainShader m_Shader;
    Terrain *m_Terrain{};

    std::vector<Texture> m_Textures;

public:
    TerrainRenderer();

    void render(const Camera &camera, const Light &light, GLuint shadowMap) const;

    void addTerrain(Terrain &terrain);

private:
    void prepareRendering() const;

    static void finishRendering();

    void renderShadow(GLuint shadowMap, const Light &light) const;
};


#endif //SURVIVE_TERRAINRENDERER_H
