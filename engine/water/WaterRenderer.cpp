//
// Created by david on 22. 02. 2021..
//

#include "WaterRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"
#include "../display/Display.h"


void WaterRenderer::render(const Camera &camera, const Light &light, const Texture &reflectionTexture,
						   const Texture &refractionTexture) const
{
	prepareRendering(camera);

	for (auto const &waterTile : m_Tiles)
	{
		auto const &water = waterTile.get();
		Renderer3DUtil::prepareEntity(water.m_Texture);

		bindTextures(water, reflectionTexture, refractionTexture);
		loadUniforms(camera, water, light);

		glDrawElements(GL_TRIANGLES, water.m_Texture.vertexCount(), GL_UNSIGNED_INT, nullptr);

		Renderer3DUtil::finishRenderingEntity();
	}

	finishRendering();
}

void WaterRenderer::prepareRendering(const Camera &camera) const
{
	Renderer3DUtil::prepareRendering(m_Shader);
	Renderer3DUtil::addTransparency(false, true);

	m_Shader.loadProjectionMatrix(Maths::projectionMatrix);
	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
}

void WaterRenderer::finishRendering()
{
	Renderer3DUtil::addTransparency(false, false);
	Renderer3DUtil::finishRendering();
}

void WaterRenderer::addWaterTile(WaterTile &waterTile)
{
	m_Tiles.emplace_back(waterTile);
}

bool WaterRenderer::shouldRender() const
{
	return !m_Tiles.empty();
}

void WaterRenderer::loadMoveFactor(const WaterShader &shader)
{
	static float moveFactor = 0;

	auto deltaTime = static_cast<float>(Display::getFrameTime());
	moveFactor += WAVE_SPEED * deltaTime;
	moveFactor = std::fmod(moveFactor, 1);

	shader.loadMoveFactor(moveFactor);
}

void WaterRenderer::loadUniforms(const Camera &camera, const WaterTile &waterTile, const Light &light) const
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(waterTile.m_Position, waterTile.m_Scale);
	m_Shader.loadTransformationMatrix(transformationMatrix);

	m_Shader.loadTextures();
	m_Shader.loadCameraPosition(camera.m_Position);
	loadMoveFactor(m_Shader);

	m_Shader.loadLight(light);
}

void WaterRenderer::bindTextures(const WaterTile &waterTile, const Texture &reflectionTexture,
								 const Texture &refractionTexture)
{
	reflectionTexture.bindTexture(0);
	refractionTexture.bindTexture(1);
	waterTile.getDuDvMap().bindTexture(2);
	waterTile.getNormalMap().bindTexture(3);
}
