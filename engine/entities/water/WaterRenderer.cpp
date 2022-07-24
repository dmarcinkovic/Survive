//
// Created by david on 22. 02. 2021..
//

#include "WaterRenderer.h"
#include "Display.h"
#include "Maths.h"
#include "Renderer3D.h"

void Survive::WaterRenderer::render(entt::registry &registry, const Camera &camera, const Light &light) const
{
	constexpr int numberOfVaoUnits = 1;
	auto waterTiles = registry.view<Render3DComponent, Transform3DComponent, TexturedComponent, MoveComponent, TagComponent>();

	prepareRenderingWater(camera);
	waterTiles.each(
			[&](Render3DComponent &renderComponent, Transform3DComponent &transform, TexturedComponent &textures,
				MoveComponent &moveComponent, TagComponent &) {
				prepareEntity(renderComponent.texturedModel, numberOfVaoUnits);

				bindTextures(textures, m_Fbo.reflectionColorTexture(), m_Fbo.refractionColorTexture(),
							 m_Fbo.getRefractionDepthBuffer());

				loadUniforms(camera, transform, moveComponent, light);
				glDrawElements(GL_TRIANGLES, renderComponent.texturedModel.vertexCount(), GL_UNSIGNED_INT, nullptr);

				finishRenderingEntity(numberOfVaoUnits);
			});

	finishRenderingWater();
}

void Survive::WaterRenderer::prepareRenderingWater(const Camera &camera) const
{
	prepareRendering(m_Shader);
	addTransparency(false, true);

	m_Shader.loadProjectionMatrix(camera.getProjectionMatrix());
	m_Shader.loadViewMatrix(camera.getViewMatrix());
}

void Survive::WaterRenderer::finishRenderingWater()
{
	addTransparency(false, false);
	finishRendering();
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

void Survive::WaterRenderer::loadUniforms(const Camera &camera, const Transform3DComponent &transform,
										  MoveComponent &moveComponent, const Light &light) const
{
	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(transform.position, transform.scale);
	m_Shader.loadTransformationMatrix(transformationMatrix);

	m_Shader.loadTextures();
	m_Shader.loadCameraPosition(camera.getPosition());
	loadMoveFactor(m_Shader, moveComponent);

	m_Shader.loadNearAndFar(camera.nearPlane, camera.farPlane);
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
