//
// Created by david on 22. 05. 2020..
//

#include "Renderer3D.h"
#include "../../constant/Constants.h"
#include "../../components/ShadowComponent.h"
#include "../display/Display.h"

Survive::Renderer3D::Renderer3D(const Light &light)
		: m_Light(light), m_ObjectRenderer(light),
		  m_ShadowMap(m_FrameBuffer.attachToDepthBufferTexture(Constants::SHADOW_WIDTH, Constants::SHADOW_HEIGHT)),
		  m_AnimationRenderer(light), m_ReflectionCLippingPlane{0, 1, 0, -Constants::WATER_HEIGHT},
		  m_RefractionCLippingPlane{0, -1, 0, Constants::WATER_HEIGHT},
		  m_BloomRenderer(Constants::BLOOM_WIDTH, Constants::BLOOM_HEIGHT)
{
}

void Survive::Renderer3D::renderScene(entt::registry &registry, Camera &camera, const glm::vec4 &plane) const
{
	m_ObjectRenderer.render(registry, camera, m_ShadowMap, plane);
	m_TerrainRenderer.render(registry, camera, m_Light, m_ShadowMap, plane);
	m_AnimationRenderer.render(registry, camera, plane);

	m_SkyRenderer.render(registry, camera, plane);
}

void Survive::Renderer3D::render(entt::registry &registry, Camera &camera) const
{
	m_MousePicking.render(registry, camera);

	m_FrameBuffer.renderToFrameBuffer(registry, m_ShadowRenderer, camera, m_Light, Constants::SHADOW_WIDTH,
									  Constants::SHADOW_HEIGHT);

	renderToWaterFrameBuffers(registry, camera);
	m_BloomRenderer.render(registry);
	renderScene(registry, camera);

	m_WaterRenderer.render(registry, camera, m_Light);
	m_OutlineRenderer.render(registry, camera);
}

void Survive::Renderer3D::addSkyboxEntity(entt::entity sky)
{
	m_SkyRenderer.addSkyEntity(sky);
}

void Survive::Renderer3D::addOutlineToObject(entt::registry &registry, entt::entity entity)
{
	m_OutlineRenderer.add3DObject(registry, entity);
}

void Survive::Renderer3D::removeOutlineToObject(entt::registry &registry)
{
	m_OutlineRenderer.removeObject(registry);
}

void Survive::Renderer3D::renderToWaterFrameBuffers(entt::registry &registry, Camera &camera) const
{
	if (WaterRenderer::shouldRender(registry))
	{
		glEnable(GL_CLIP_DISTANCE0);

		renderWaterReflection(registry, camera);
		renderWaterRefraction(registry, camera);

		glDisable(GL_CLIP_DISTANCE0);
	}
}

void Survive::Renderer3D::renderWaterReflection(entt::registry &registry, Camera &camera) const
{
	m_WaterRenderer.bindReflectionFrameBuffer();

	float distance = 2.0f * (camera.m_Position.y - Constants::WATER_HEIGHT);

	camera.moveCameraInYDirection(-distance);
	camera.invertPitch();

	Display::clearWindow();
	renderScene(registry, camera, m_ReflectionCLippingPlane);

	camera.moveCameraInYDirection(distance);
	camera.invertPitch();

	WaterFbo::unbindFrameBuffer();
}

void Survive::Renderer3D::renderWaterRefraction(entt::registry &registry, Camera &camera) const
{
	m_WaterRenderer.bindRefractionFrameBuffer();
	Display::clearWindow();
	renderScene(registry, camera, m_RefractionCLippingPlane);
	WaterFbo::unbindFrameBuffer();
}

void Survive::Renderer3D::addShadow(entt::registry &registry, entt::entity entity)
{
	m_ShadowRenderer.add3DObject(registry, entity);
	registry.emplace<ShadowComponent>(entity, true);
}