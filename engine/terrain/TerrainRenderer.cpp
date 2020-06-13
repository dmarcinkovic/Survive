//
// Created by david on 22. 05. 2020..
//

#include "TerrainRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"

TerrainRenderer::TerrainRenderer()
{
    m_Shader.start();

    auto projectionMatrix = Maths::createProjectionMatrix(fieldOfView, near, far);
    m_Shader.loadProjectionMatrix(projectionMatrix);

    Shader::stop();
}

void TerrainRenderer::render(const Camera &camera) const
{
    prepareRendering();

    auto transformationMatrix = Maths::createTransformationMatrix(m_Terrain->m_Position, m_Terrain->m_ScaleX,
                                                                  m_Terrain->m_ScaleY, m_Terrain->m_ScaleZ, 90);

    auto viewMatrix = Maths::createViewMatrix(camera);
    m_Shader.loadViewMatrix(viewMatrix);

    m_Shader.loadTransformationMatrix(transformationMatrix);
    glDrawElements(GL_TRIANGLES, m_Terrain->m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

    finishRendering();
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
