//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_SHADOWRENDERER_H
#define SURVIVE_SHADOWRENDERER_H

#include <vector>
#include <unordered_map>
#include <functional>

#include "ShadowShader.h"
#include "../light/Light.h"
#include "../objects/Object3D.h"
#include "../camera/Camera.h"
#include "ShadowBox.h"

class ShadowRenderer
{
private:
    ShadowShader m_ShadowShader{};
    std::unordered_map<TexturedModel, std::vector<std::reference_wrapper<Object3D>>, TextureHash> m_Objects;

    ShadowBox m_ShadowBox{};

public:
    ShadowRenderer();

    void render(const Light &light, const Camera &camera) const;

    void add3DObject(Object3D &object);
};


#endif //SURVIVE_SHADOWRENDERER_H
