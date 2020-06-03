//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H


#include "../objects/ObjectRenderer.h"
#include "../terrain/TerrainRenderer.h"

class Renderer3D
{
private:
    ObjectRenderer m_ObjectRenderer;
    TerrainRenderer m_TerrainRenderer;

    const Light &m_Light;

public:
    explicit Renderer3D(const Light &light);

    void render(const Camera &camera) const;

    void add3DObject(Object3D &object3D);

    void addTerrain(Terrain &terrain);
};


#endif //SURVIVE_RENDERER3D_H
