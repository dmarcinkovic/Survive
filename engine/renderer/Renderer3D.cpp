//
// Created by david on 22. 05. 2020..
//

#include "Renderer3D.h"

Renderer3D::Renderer3D(const Light &light)
        : m_Light(light)
{
    m_ObjectRenderer.setLight(light);
}

void Renderer3D::render(const Camera &camera) const
{
    m_ObjectRenderer.render(camera);
    m_TerrainRenderer.render(camera);
}

void Renderer3D::add3DObject(Object3D &object3D)
{
    m_ObjectRenderer.add3DObject(object3D);
}

void Renderer3D::addTerrain(Terrain &terrain)
{
    m_TerrainRenderer.addTerrain(terrain);
}
