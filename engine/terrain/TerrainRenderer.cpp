//
// Created by david on 22. 05. 2020..
//

#include "TerrainRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"
#include "../constant/Constants.h"

TerrainRenderer::TerrainRenderer()
{
    m_Shader.start();

    auto projectionMatrix = Maths::createProjectionMatrix(fieldOfView, Constants::NEAR, Constants::FAR);
    glm::mat4 lightProjection = Maths::createLightProjectionMatrix(Constants::NEAR,
                                                                   Constants::FAR);

    m_Shader.loadLightProjectionMatrix(lightProjection);
    m_Shader.loadProjectionMatrix(projectionMatrix);

    Shader::stop();
}

void TerrainRenderer::render(const Camera &camera, const Light &light, GLuint shadowMap) const
{
    prepareRendering();
    renderShadow(shadowMap, light);

    auto viewMatrix = Maths::createViewMatrix(camera);
    m_Shader.loadViewMatrix(viewMatrix);

    auto transformationMatrix = Maths::createTransformationMatrix(m_Terrain->m_Position, m_Terrain->m_ScaleX,
                                                                  m_Terrain->m_ScaleY, m_Terrain->m_ScaleZ, rotationX);
    m_Shader.loadTransformationMatrix(transformationMatrix);
    glDrawElements(GL_TRIANGLES, m_Terrain->m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

    finishRendering();
}

void TerrainRenderer::renderShadow(GLuint shadowMap, const Light &light) const
{
    glm::mat4 lightView = Maths::createLightViewMatrix(light);
    m_Shader.loadLightViewMatrix(lightView);

    Texture texture(shadowMap);
    texture.bindTexture(0);
}

void TerrainRenderer::addTerrain(Terrain &terrain)
{
    m_Terrain = &terrain;
}

void TerrainRenderer::prepareRendering() const
{
    Renderer3DUtil::prepareRendering(m_Shader);
    Renderer3DUtil::prepareEntity(m_Terrain->m_Texture);
    Renderer3DUtil::addTransparency(false, true);
}

void TerrainRenderer::finishRendering()
{
    Texture::unbindTexture();
    Renderer3DUtil::addTransparency(true, false);
    Renderer3DUtil::finishRenderingEntity();
    Renderer3DUtil::finishRendering();
}


