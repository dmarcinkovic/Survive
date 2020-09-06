//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H

#include "../objects/ObjectRenderer.h"
#include "../terrain/TerrainRenderer.h"
#include "../fbo/FrameBuffer.h"
#include "../animation/AnimationRenderer.h"

class Renderer3D
{
private:
    ObjectRenderer m_ObjectRenderer;
    TerrainRenderer m_TerrainRenderer;
    ShadowRenderer m_ShadowRenderer;
    AnimationRenderer m_AnimationRenderer;

    const Light &m_Light;
    FrameBuffer m_FrameBuffer;
    const GLuint m_ShadowMap;

public:
    explicit Renderer3D(const Light &light);

    void render(const Camera &camera) const;

    void add3DObject(Object3D &object3D);

    void addTerrain(Terrain &terrain);

    void addAnimatedObject(Object3D &object3D);
};


#endif //SURVIVE_RENDERER3D_H
