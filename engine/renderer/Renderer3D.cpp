//
// Created by david on 22. 05. 2020..
//

#include "Renderer3D.h"

void Renderer3D::render(const Camera &camera) const
{
    objectRenderer.render(camera);
}

void Renderer3D::add3DObject(Object3D &object3D)
{
    objectRenderer.add3DObject(object3D);
}
