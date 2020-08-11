//
// Created by david on 22. 05. 2020..
//

#include <glm/glm.hpp>

#include "ShadowRenderer.h"
#include "../math/Maths.h"
#include "../renderer/Renderer3DUtil.h"
#include "../constant/Constants.h"

ShadowRenderer::ShadowRenderer()
{
    m_ShadowShader.start();

    glm::mat4 projectionMatrix = Maths::createLightProjectionMatrix(Constants::NEAR,
                                                                    Constants::FAR);
    m_ShadowShader.loadProjectionMatrix(projectionMatrix);

    ShadowShader::stop();
}

void ShadowRenderer::render(const Light &light, const Camera &camera) const
{
    static const glm::mat4 lightViewMatrix = Maths::createLightViewMatrix(light);
    m_ShadowBox.calculateShadowBox(camera, lightViewMatrix);

    Renderer3DUtil::prepareRendering(m_ShadowShader);
    glm::mat4 viewMatrix = Maths::createLightViewMatrix(light);
    m_ShadowShader.loadViewMatrix(viewMatrix);

    for (auto const&[texture, objects] : m_Objects)
    {
        texture.bind();
        glEnableVertexAttribArray(0);
        for (auto const &object : objects)
        {
            const Object3D &o = object.get();

            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);

            auto rotation = o.m_Rotation + camera.m_Rotation;
            glm::mat4 modelMatrix = Maths::createTransformationMatrix(o.m_Position, o.m_ScaleX, o.m_ScaleY, o.m_ScaleZ,
                                                                      rotation.x, rotation.y, rotation.z);
            m_ShadowShader.loadTransformationMatrix(modelMatrix);

            glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());
            glDisable(GL_CULL_FACE);
        }

        Texture::unbindTexture();
        glDisableVertexAttribArray(0);
    }

    Renderer3DUtil::finishRendering();
}

void ShadowRenderer::add3DObject(Object3D &object)
{
    auto &batch = m_Objects[object.m_Texture];
    batch.emplace_back(object);
}
