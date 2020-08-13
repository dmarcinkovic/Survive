//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H


#include "../objects/ObjectRenderer.h"
#include "../animation/AnimationRenderer.h"

class Renderer3D
{
private:
    ObjectRenderer m_ObjectRenderer;
    AnimationRenderer m_AnimationRenderer;

    const Light &m_Light;

public:
    explicit Renderer3D(const Light &light);

    void render(const Camera &camera) const;

    void add3DObject(Object3D &object3D);

    void addAnimatedObject(Object3D &object3D);
};


#endif //SURVIVE_RENDERER3D_H
