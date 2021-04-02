//
// Created by david on 22. 02. 2021..
//

#include "WaterRenderer.h"
#include "../renderer/Renderer3DUtil.h"
#include "../math/Maths.h"
#include "../display/Display.h"
#include "../constant/Constants.h"

void WaterRenderer::render(entt::registry &registry, const Camera &camera, const Light &light) const
{
	auto waterTiles = registry.group<RenderComponent, Transform3DComponent, TexturedComponent, MoveComponent>();
	if (waterTiles.empty())
	{
		return;
	}

	prepareRendering(camera);
	waterTiles.each([&](RenderComponent &renderComponent, Transform3DComponent &transform, TexturedComponent &textures,
						MoveComponent &moveComponent) {
		Renderer3DUtil::prepareEntity(renderComponent.texturedModel);

		bindTextures(textures, m_Fbo.reflectionColorTexture(), m_Fbo.refractionColorTexture(),
					 m_Fbo.getRefractionDepthBuffer());

		loadUniforms(camera, transform, moveComponent, light);
		glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);

		Renderer3DUtil::finishRenderingEntity();
	});
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

bool WaterRenderer::shouldRender(entt::registry &registry)
{
	auto group = registry.group<RenderComponent, Transform3DComponent, TexturedComponent, MoveComponent>();
	return !group.empty();
}

void WaterRenderer::loadMoveFactor(const WaterShader &shader, MoveComponent &moveComponent)
{
	auto deltaTime = static_cast<float>(Display::getFrameTime());
	moveComponent.currentMoveValue += moveComponent.moveSpeed * deltaTime;
	moveComponent.currentMoveValue = std::fmod(moveComponent.currentMoveValue, 1);

	shader.loadMoveFactor(moveComponent.currentMoveValue);
}

void
WaterRenderer::loadUniforms(const Camera &camera, const Transform3DComponent &transform, MoveComponent &moveComponent,
							const Light &light) const
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale);
	m_Shader.loadTransformationMatrix(transformationMatrix);

	m_Shader.loadTextures();
	m_Shader.loadCameraPosition(camera.m_Position);
	loadMoveFactor(m_Shader, moveComponent);

	m_Shader.loadNearAndFar(Constants::NEAR, Constants::FAR);
	m_Shader.loadLight(light);
}

void WaterRenderer::bindTextures(const TexturedComponent &textures, const Texture &reflectionTexture,
								 const Texture &refractionTexture, const Texture &refractionDepthMap)
{
	reflectionTexture.bindTexture(0);
	refractionTexture.bindTexture(1);
	textures.textures[0].bindTexture(2);
	textures.textures[1].bindTexture(3);
	refractionDepthMap.bindTexture(4);
}

void WaterRenderer::bindReflectionFrameBuffer() const
{
	m_Fbo.bindReflectionFrameBuffer();
}

void WaterRenderer::bindRefractionFrameBuffer() const
{
	m_Fbo.bindRefractionFrameBuffer();
}
