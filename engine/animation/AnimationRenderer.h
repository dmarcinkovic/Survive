//
// Created by david on 12. 08. 2020..
//

#ifndef SURVIVE_ANIMATIONRENDERER_H
#define SURVIVE_ANIMATIONRENDERER_H

#include <vector>
#include <functional>

#include "AnimationShader.h"
#include "../light/Light.h"
#include "../objects/Object3D.h"

class AnimationRenderer
{
private:
    constexpr static const float fieldOfView = 70.0f;
    constexpr static const float near = 0.1f;
    constexpr static const float far = 1000.0f;

    AnimationShader m_Shader;

    std::vector<std::reference_wrapper<Object3D>> m_Objects;
    const Light &m_Light;

public:
    explicit AnimationRenderer(const Light &light);

    void render() const;

    void addObject(Object3D &object);
};


#endif //SURVIVE_ANIMATIONRENDERER_H
