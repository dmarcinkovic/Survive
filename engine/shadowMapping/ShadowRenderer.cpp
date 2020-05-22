//
// Created by david on 22. 05. 2020..
//

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "ShadowRenderer.h"
#include "../math/Maths.h"

ShadowRenderer::ShadowRenderer()
{
    m_ShadowShader.start();

    glm::mat4 projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near, far);
    m_ShadowShader.loadProjectionMatrix(projectionMatrix);
    m_ShadowShader.loadProjectionMatrix(Maths::createProjectionMatrix(70, near, far));

    ShadowShader::stop();
}

void ShadowRenderer::render(const Light &light, const Camera &camera) const
{
    m_ShadowShader.start();
    glEnable(GL_DEPTH_TEST);

    for (auto const&[texture, objects] : m_Objects)
    {
        texture.bindTexture();
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

            glm::mat4 viewMatrix = glm::lookAt(light.position(), glm::vec3{0.0f}, glm::vec3{0, 1, 0});
            viewMatrix = Maths::createViewMatrix(camera);
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
