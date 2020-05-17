//
// Created by david on 17. 05. 2020..
//

#include "ObjectRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"

ObjectRenderer::ObjectRenderer()
{
    m_Shader.start();
    m_Shader.loadProjectionMatrix(Maths::createProjectionMatrix(fieldOfView, near, far));
    Shader::stop();
}

void ObjectRenderer::render(const Camera &camera) const
{
    Renderer3DUtil::prepareRendering(m_Shader, false, false);

    m_Shader.loadLight(m_LightPosition, m_LightColor);

    for (auto const&[texture, objects] : m_Objects)
    {
        Renderer3DUtil::prepareEntity(texture);
        for (auto const &object : objects)
        {
            const Object3D &o = object.get();

            auto rotation = camera.m_Rotation + o.m_Rotation;

            m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
            m_Shader.loadTransformationMatrix(Maths::createTransformationMatrix(o.m_Position,
                                                                                o.m_ScaleX, o.m_ScaleY, o.m_ScaleZ,
                                                                                rotation.x, rotation.y,
                                                                                rotation.z));

            glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());
        }

        Renderer3DUtil::finishRenderingEntity();
    }
    Renderer3DUtil::finishRendering();
}

void ObjectRenderer::add3DObject(Object3D &entity)
{
    auto &batch = m_Objects[entity.m_Texture];
    batch.emplace_back(entity);
}

void ObjectRenderer::setLight(const Light &light)
{
    m_LightPosition = light.position();
    m_LightColor = light.color();
}
