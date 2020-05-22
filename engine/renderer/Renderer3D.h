//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H


#include "../objects/ObjectRenderer.h"

class Renderer3D
{
private:
    ObjectRenderer objectRenderer;

public:
    void render(const Camera &camera) const;

    void add3DObject(Object3D &object3D);

    void addLight(const Light &light);
};


#endif //SURVIVE_RENDERER3D_H
