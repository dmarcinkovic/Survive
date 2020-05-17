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

    for (auto const&[texture, objects] : m_Objects)
    {
        Renderer3DUtil::prepareEntity(texture);
        for (auto const &object : objects)
        {
            const Entity &e = object.get();

            m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
            m_Shader.loadTransformationMatrix(Maths::createTransformationMatrix(e.m_Position));
            glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());
        }

        Renderer3DUtil::finishRenderingEntity();
    }

    Renderer3DUtil::finishRendering();
}

void ObjectRenderer::add3DObject(Entity &entity)
{
    std::vector<std::reference_wrapper<Entity>> &batch = m_Objects[entity.m_Texture];
    batch.emplace_back(entity);
}
