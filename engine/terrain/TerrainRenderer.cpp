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

void TerrainRenderer::render(const Camera &camera, const Light &light, GLuint shadowMap) const
{
    prepareRendering();

    auto transformationMatrix = Maths::createTransformationMatrix(m_Terrain.m_Position, m_Terrain.m_ScaleX,
                                                                  m_Terrain.m_ScaleY, m_Terrain.m_ScaleZ, 90);

    glm::mat4 lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.1f, 100.0f);
    glm::mat4 lightView = glm::lookAt(light.position(), glm::vec3{0.0f}, glm::vec3{0, 1, 0});
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    m_Shader.loadLightSpaceMatrix(lightSpaceMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowMap);

    auto viewMatrix = Maths::createViewMatrix(camera);
    m_Shader.loadViewMatrix(viewMatrix);

    m_Shader.loadTransformationMatrix(transformationMatrix);
    glDrawElements(GL_TRIANGLES, m_Terrain.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
    finishRendering();
}

void TerrainRenderer::addTerrain(Terrain &terrain)
{
    m_Terrain = terrain;
}

void TerrainRenderer::prepareRendering() const
{
    Renderer3DUtil::prepareRendering(m_Shader);
    Renderer3DUtil::prepareEntity(m_Terrain.m_Texture);
    Renderer3DUtil::addTransparency(false, true);
}

void TerrainRenderer::finishRendering() const
{
    Renderer3DUtil::addTransparency(true, false);
    Renderer3DUtil::finishRenderingEntity();
    Renderer3DUtil::finishRendering();
}


