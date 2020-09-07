//
// Created by david on 17. 05. 2020..
//
#include "ObjectRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"
#include "../constant/Constants.h"

ObjectRenderer::ObjectRenderer(const Light &light)
        : m_Light(light)
{
    m_Shader.start();

    const glm::mat4 projectionMatrix = Maths::createProjectionMatrix(fieldOfView, Constants::NEAR, Constants::FAR);
    m_Shader.loadProjectionMatrix(projectionMatrix);

    const glm::mat4 lightProjection = Maths::createLightProjectionMatrix(Constants::NEAR, Constants::FAR);
    m_Shader.loadLightProjection(lightProjection);

    Shader::stop();
}

void ObjectRenderer::render(const Camera &camera, GLuint shadowMap) const
{
    Renderer3DUtil::prepareRendering(m_Shader);

    const glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    const glm::mat4 lightViewMatrix = Maths::createLightViewMatrix(m_Light);
    m_Shader.loadLight(m_Light.position(), m_Light.color(), 0.7, 3);

    m_Shader.loadViewMatrix(viewMatrix);
    m_Shader.loadLightViewMatrix(lightViewMatrix);
    m_Shader.loadTextures();

    Texture texture(shadowMap);
    texture.bindTexture(1);
    m_Shader.loadCameraPosition(camera.m_Position);

    for (auto const&[texturedModel, objects] : m_Objects)
    {
        Renderer3DUtil::prepareEntity(texturedModel);
        renderScene(objects, camera);

        Renderer3DUtil::finishRenderingEntity();
    }

    Renderer3DUtil::finishRendering();
}

void ObjectRenderer::add3DObject(Object3D &entity)
{
    auto &batch = m_Objects[entity.m_Texture];
    batch.emplace_back(entity);
}

void
ObjectRenderer::renderScene(const std::vector<std::reference_wrapper<Object3D>> &objects, const Camera &camera) const
{
    for (auto const &object : objects)
    {
        auto const &o = object.get();
        auto rotation = camera.m_Rotation + o.m_Rotation;

        glm::mat4 modelMatrix = Maths::createTransformationMatrix(o.m_Position, o.m_ScaleX, o.m_ScaleY, o.m_ScaleZ,
                                                                  rotation.x, rotation.y, rotation.z);
        m_Shader.loadTransformationMatrix(modelMatrix);
        Renderer3DUtil::addTransparency(!o.m_IsTransparent, !o.m_IsTransparent);

        glDrawArrays(GL_TRIANGLES, 0, o.m_Texture.vertexCount());

        Renderer3DUtil::addTransparency(o.m_IsTransparent, o.m_IsTransparent);
    }
}

