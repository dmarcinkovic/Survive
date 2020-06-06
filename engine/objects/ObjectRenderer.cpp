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
    Renderer3DUtil::prepareRendering(m_Shader);

    const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    m_Shader.loadViewMatrix(viewMatrix);

    m_Shader.loadLight(m_LightPosition, m_LightColor);

    for (auto const&[texture, objects] : m_Objects)
    {
        Renderer3DUtil::prepareEntity(texture);
        for (auto const &object : objects)
        {
            const Object3D &o = object.get();
            auto rotation = camera.m_Rotation + o.m_Rotation;

            auto modelMatrix = Maths::createTransformationMatrix(o.m_Position, o.m_ScaleX, o.m_ScaleY, o.m_ScaleZ,
                                                                 rotation.x, rotation.y, rotation.z);

            renderScene(modelMatrix, o);
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

void ObjectRenderer::renderScene(const glm::mat4 &transformationMatrix, const Object3D &object3D) const
{
    m_Shader.loadTransformationMatrix(transformationMatrix);
    Renderer3DUtil::addTransparency(!object3D.m_IsTransparent, !object3D.m_IsTransparent);

    glDrawArrays(GL_TRIANGLES, 0, object3D.m_Texture.vertexCount());

    Renderer3DUtil::addTransparency(object3D.m_IsTransparent, object3D.m_IsTransparent);
}
