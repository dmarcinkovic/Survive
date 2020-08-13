//
// Created by david on 12. 08. 2020..
//

#include "AnimationRenderer.h"
#include "../math/Maths.h"
#include "../renderer/Renderer3DUtil.h"

AnimationRenderer::AnimationRenderer(const Light &light)
        : m_Light(light)
{
    m_Shader.start();

    auto projectionMatrix = Maths::createProjectionMatrix(fieldOfView, near, far);
    m_Shader.loadProjectionMatrix(projectionMatrix);

    AnimationShader::stop();
}

void AnimationRenderer::render(const Camera &camera) const
{
    Renderer3DUtil::prepareRendering(m_Shader);

    const auto viewMatrix = Maths::createViewMatrix(camera);
    m_Shader.loadViewMatrix(viewMatrix);
    m_Shader.loadLight(m_Light.position(), m_Light.color());

    for (auto const &object : m_Objects)
    {
        Renderer3DUtil::prepareEntity(object.get().m_Texture);

        renderObject(object.get(), camera);

        Renderer3DUtil::finishRenderingEntity();
    }

    Renderer3DUtil::finishRendering();
}

void AnimationRenderer::addObject(Object3D &object)
{
    m_Objects.emplace_back(object);
}

void AnimationRenderer::renderObject(const Object3D &object, const Camera &camera) const
{
    auto rotation = object.m_Rotation + camera.m_Rotation;

    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(object.m_Position, object.m_ScaleX,
                                                                       object.m_ScaleY, object.m_ScaleZ, rotation.x,
                                                                       rotation.y, rotation.z);
    m_Shader.loadTransformationMatrix(transformationMatrix);

    Renderer3DUtil::addTransparency(!object.m_IsTransparent, !object.m_IsTransparent);
    glDrawArrays(GL_TRIANGLES, 0, object.m_Texture.vertexCount());
    Renderer3DUtil::addTransparency(object.m_IsTransparent, object.m_IsTransparent);
}