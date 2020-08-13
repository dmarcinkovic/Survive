//
// Created by david on 12. 08. 2020..
//

#include "AnimationRenderer.h"
#include "../math/Maths.h"

AnimationRenderer::AnimationRenderer(const Light& light)
    : m_Light(light)
{
    m_Shader.start();

    auto projectionMatrix = Maths::createProjectionMatrix(fieldOfView, near, far);
    m_Shader.loadProjectionMatrix(projectionMatrix);

    AnimationShader::stop();
}

void AnimationRenderer::render() const
{

}

void AnimationRenderer::addObject(Object3D &object)
{
    m_Objects.emplace_back(object);
}
