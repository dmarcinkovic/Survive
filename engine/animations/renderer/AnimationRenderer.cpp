//
// Created by david on 17. 05. 2020..
//
#include <iostream>
#include "AnimationRenderer.h"
#include "../../renderer/Renderer3DUtil.h"
#include "../../math/Maths.h"
#include "../../constant/Constants.h"

AnimationRenderer::AnimationRenderer(const Light &light)
        : m_Light(light)
{
    m_Shader.start();
    m_Shader.loadProjectionMatrix(Maths::createProjectionMatrix(Constants::FOV));
    Shader::stop();
}

void AnimationRenderer::render(const Camera &camera) const
{
    Renderer3DUtil::prepareRendering(m_Shader);

    const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    m_Shader.loadViewMatrix(viewMatrix);

    m_Shader.loadLight(m_Light.position(), m_Light.color());

    for (auto const&[texture, objects] : m_Objects)
    {
        Renderer3DUtil::prepareEntity(texture);
        renderScene(objects, camera);

        Renderer3DUtil::finishRenderingEntity();
    }

    Renderer3DUtil::finishRendering();
}

void AnimationRenderer::addAnimatedModel(AnimatedObject &entity)
{
    auto &batch = m_Objects[entity.m_Texture];
    batch.emplace_back(entity);
}

void
AnimationRenderer::renderScene(const std::vector<std::reference_wrapper<AnimatedObject>> &objects,
                               const Camera &camera) const
{
    for (auto const &object : objects)
    {
        auto const &o = object.get();
        auto rotation = camera.m_Rotation + o.m_Rotation;

        glm::mat4 modelMatrix = Maths::createTransformationMatrix(o.m_Position, o.m_ScaleX, o.m_ScaleY, o.m_ScaleZ,
                                                                  rotation.x, rotation.y, rotation.z);
        m_Shader.loadTransformationMatrix(modelMatrix);
        Renderer3DUtil::addTransparency(!o.m_IsTransparent, !o.m_IsTransparent);

        auto const &transforms = object.get().getJointTransforms();

//        for (int k = 0; k < 4; ++k)
//        {
//            for (const auto &transform : transforms)
//            {
//                for (int j = 0; j < 4; ++j)
//                {
//                    std::cout << transform[k][j] << ' ';
//                }
//                std::cout << "  ";
//            }
//            std::cout << '\n';
//        }
//        std::cout << '\n';

        m_Shader.loadJointTransforms(object.get().getJointTransforms());

        glDrawArrays(GL_TRIANGLES, 0, o.m_Texture.vertexCount());

        Renderer3DUtil::addTransparency(o.m_IsTransparent, o.m_IsTransparent);
    }
}