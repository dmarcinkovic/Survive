//
// Created by david on 22. 02. 2021..
//

#include "WaterRenderer.h"
#include "Constants.h"
#include "Display.h"
#include "Maths.h"
#include "Renderer3DUtil.h"

void Survive::WaterRenderer::render(entt::registry &registry, const Camera &camera, const Light &light) const
{
	auto waterTiles = registry.view<Render3DComponent, Transform3DComponent, TexturedComponent, MoveComponent>();

	prepareRendering(camera);
	waterTiles.each([&](Render3DComponent &renderComponent, Transform3DComponent &transform, TexturedComponent &textures,
						MoveComponent &moveComponent) {
		Renderer3DUtil::prepareEntity(renderComponent.texturedModel);

		bindTextures(textures, m_Fbo.reflectionColorTexture(), m_Fbo.refractionColorTexture(),
					 m_Fbo.getRefractionDepthBuffer());

		loadUniforms(camera, transform, moveComponent, light);
		glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);

		Renderer3DUtil::finishRenderingEntity();
	});

	finishRendering();
}

void Survive::WaterRenderer::prepareRendering(const Camera &camera) const
{
	Renderer3DUtil::prepareRendering(m_Shader);
	Renderer3DUtil::addTransparency(false, true);

	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_Shader.loadViewMatrix(Maths::createViewMatrix(camera));
}

void Survive::WaterRenderer::finishRendering()
{
	Renderer3DUtil::addTransparency(false, false);
	Renderer3DUtil::finishRendering();
}

bool Survive::WaterRenderer::shouldRender(entt::registry &registry)
{
	auto group = registry.group<Render3DComponent, Transform3DComponent, TexturedComponent, MoveComponent>();
	return !group.empty();
}

void Survive::WaterRenderer::loadMoveFactor(const WaterShader &shader, MoveComponent &moveComponent)
{
	auto deltaTime = static_cast<float>(Display::getFrameTime());
	moveComponent.currentMoveValue += moveComponent.moveSpeed * deltaTime;
	moveComponent.currentMoveValue = static_cast<float>(std::fmod(moveComponent.currentMoveValue, 1));

	shader.loadMoveFactor(moveComponent.currentMoveValue);
}

void
Survive::WaterRenderer::loadUniforms(const Camera &camera, const Transform3DComponent &transform,
									 MoveComponent &moveComponent, const Light &light) const
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale);
	m_Shader.loadTransformationMatrix(transformationMatrix);

	m_Shader.loadTextures();
	m_Shader.loadCameraPosition(camera.position);
	loadMoveFactor(m_Shader, moveComponent);

	m_Shader.loadNearAndFar(Constants::NEAR, Constants::FAR);
	m_Shader.loadLight(light);
}

void Survive::WaterRenderer::bindTextures(const TexturedComponent &textures, const Texture &reflectionTexture,
										  const Texture &refractionTexture, const Texture &refractionDepthMap)
{
	reflectionTexture.bindTexture(0);
	refractionTexture.bindTexture(1);
	textures.textures[0].bindTexture(2);
	textures.textures[1].bindTexture(3);
	refractionDepthMap.bindTexture(4);
}

void Survive::WaterRenderer::bindReflectionFrameBuffer() const
{
	m_Fbo.bindReflectionFrameBuffer();
}

void Survive::WaterRenderer::bindRefractionFrameBuffer() const
{
	m_Fbo.bindRefractionFrameBuffer();
}
