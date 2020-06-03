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

class ShadowRenderer
{
private:
    constexpr static const float near = 0.1f;
    constexpr static const float far = 100.0f;

    ShadowShader m_ShadowShader{};
    std::unordered_map<Texture, std::vector<std::reference_wrapper<Object3D>>, TextureHash> m_Objects;

public:
    ShadowRenderer();

    void render(const Light &light, const Camera &camera) const;

    void add3DObject(Object3D &object);
};


#endif //SURVIVE_SHADOWRENDERER_H
