//
// Created by david on 22. 05. 2020..
//

#include <glm/glm.hpp>

#include "ShadowRenderer.h"
#include "../math/Maths.h"

ShadowRenderer::ShadowRenderer()
{
    m_ShadowShader.start();

    glm::mat4 projectionMatrix = Maths::createLightProjectionMatrix(-50.0f, 50.0f, -50.0f, 50.0f, near, far);
    m_ShadowShader.loadProjectionMatrix(projectionMatrix);

    ShadowShader::stop();
}

void ShadowRenderer::render(const Light &light, const Camera &camera) const
{
    m_ShadowShader.start();
    glEnable(GL_DEPTH_TEST);

    for (auto const&[texture, objects] : m_Objects)
    {
        texture.bind();
        glEnableVertexAttribArray(0);
        for (auto const &object : objects)
        {
            const Object3D &o = object.get();

            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);

            auto rotation = o.m_Rotation + camera.m_Rotation;
            glm::mat4 modelMatrix = Maths::createTransformationMatrix(o.m_Position, o.m_ScaleX, o.m_ScaleY, o.m_ScaleZ,
                                                                      rotation.x, rotation.y, rotation.z);
            m_ShadowShader.loadTransformationMatrix(modelMatrix);

            glm::mat4 viewMatrix = Maths::createLightViewMatrix(light);
            m_ShadowShader.loadViewMatrix(viewMatrix);

            glDrawArrays(GL_TRIANGLES, 0, texture.vertexCount());

            glDisable(GL_CULL_FACE);
        }

        Texture::unbindTexture();
        glDisableVertexAttribArray(0);
    }

    ShadowShader::stop();
    glDisable(GL_DEPTH_TEST);
}

void ShadowRenderer::add3DObject(Object3D &object)
{
    auto &batch = m_Objects[object.m_Texture];
    batch.emplace_back(object);
}
