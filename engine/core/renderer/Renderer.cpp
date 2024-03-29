//
// Created by david on 22. 05. 2020..
//

#include "Renderer.h"
#include "Constants.h"
#include "Display.h"

Survive::Renderer::Renderer(const Light &light)
		: m_Light(light), m_ObjectRenderer(light),
		  m_ShadowMap(
				  m_ShadowFrameBuffer.attachToDepthBufferTexture(Constants::SHADOW_WIDTH, Constants::SHADOW_HEIGHT)),
		  m_AnimationRenderer(light), m_ReflectionCLippingPlane{0, 1, 0, -Constants::WATER_HEIGHT},
		  m_RefractionCLippingPlane{0, -1, 0, Constants::WATER_HEIGHT},
		  m_BloomRenderer(Constants::BLOOM_WIDTH, Constants::BLOOM_HEIGHT), m_SceneSize(Display::getWindowSize<int>())
{
	m_Scene = m_SceneFrameBuffer.createTexture(m_SceneSize.first, m_SceneSize.second);
}

void Survive::Renderer::render3DScene(entt::registry &registry, const Camera &camera, const glm::vec4 &plane) const
{
	m_ObjectRenderer.render(registry, camera, m_ShadowMap, plane);
	m_TerrainRenderer.render(registry, camera, m_Light, m_ShadowMap, plane);
	m_AnimationRenderer.renderAnimation(registry, camera, m_ShadowMap, plane);

	m_SkyRenderer.render(registry, camera, plane);
}

void Survive::Renderer::render2DScene(entt::registry &registry, const Camera &camera) const
{
	m_GuiRenderer.render(registry, camera);
	m_SpriteRenderer.render(registry, camera);

	m_TextRenderer.renderText(registry, camera);
	m_ButtonRenderer.render();
	m_WireframeRenderer.render();
	m_ParticleRenderer.render(registry, camera);
}

void Survive::Renderer::render(entt::registry &registry, Camera &camera) const
{
	m_MousePicking.render(registry, camera);

	m_ShadowFrameBuffer.renderToFrameBuffer(registry, m_ShadowRenderer, camera, m_Light, Constants::SHADOW_WIDTH,
											Constants::SHADOW_HEIGHT);

	renderToWaterFrameBuffers(registry, camera);
	m_BloomRenderer.render(registry);
	render3DScene(registry, camera);

	m_WaterRenderer.render(registry, camera, m_Light);
	m_OutlineRenderer.render(registry, camera);

	render2DScene(registry, camera);
}

Survive::Texture Survive::Renderer::getRenderedTexture() const
{
	return Texture(m_Scene);
}

void Survive::Renderer::resetViewport()
{
	auto[width, height] = Display::getWindowSize<int>();
	glViewport(0, 0, width, height);
}

void Survive::Renderer::renderToWaterFrameBuffers(entt::registry &registry, Camera &camera) const
{
	if (WaterRenderer::shouldRender(registry))
	{
		glEnable(GL_CLIP_DISTANCE0);

		renderWaterReflection(registry, camera);
		renderWaterRefraction(registry, camera);

		glDisable(GL_CLIP_DISTANCE0);
	}
}

void Survive::Renderer::renderWaterReflection(entt::registry &registry, Camera &camera) const
{
	m_WaterRenderer.bindReflectionFrameBuffer();

	float distance = 2.0f * (camera.getPosition().y - Constants::WATER_HEIGHT);

	camera.moveCameraInYDirection(-distance);
	camera.invertPitch();

	Display::clearWindow();
	render3DScene(registry, camera, m_ReflectionCLippingPlane);

	camera.moveCameraInYDirection(distance);
	camera.invertPitch();

	WaterFbo::unbindFrameBuffer();
}

void Survive::Renderer::renderWaterRefraction(entt::registry &registry, const Camera &camera) const
{
	m_WaterRenderer.bindRefractionFrameBuffer();

	Display::clearWindow();
	render3DScene(registry, camera, m_RefractionCLippingPlane);
	WaterFbo::unbindFrameBuffer();
}

void Survive::Renderer::setMousePickingPosition(float mouseX, float mouseY)
{
	m_MousePicking.setMousePosition(mouseX, mouseY);
}

void Survive::Renderer::addMousePickingListener(const MousePickingListener &listener)
{
	m_MousePicking.addListener(listener);
}

void Survive::Renderer::popMousePickingListener()
{
	m_MousePicking.popListener();
}

void Survive::Renderer::renderScene(entt::registry &registry, Camera &camera, bool renderEditor) const
{
	m_ShadowFrameBuffer.renderToFrameBuffer(registry, m_ShadowRenderer, camera, m_Light, Constants::SHADOW_WIDTH,
											Constants::SHADOW_HEIGHT);

	renderToWaterFrameBuffers(registry, camera);
	m_SceneFrameBuffer.bindFrameBuffer();
	Display::clearWindow();

	if (renderEditor)
	{
		m_MousePicking.render(registry, camera);
	}

	glViewport(0, 0, m_SceneSize.first, m_SceneSize.second);
	render3DScene(registry, camera);
	m_WaterRenderer.render(registry, camera, m_Light);

	if (renderEditor)
	{
		m_OutlineRenderer.render(registry, camera);
	}

	render2DScene(registry, camera);

	FrameBuffer::unbindFrameBuffer();

	m_BloomRenderer.render(registry);
	resetViewport();
}

void Survive::Renderer::addButton(Survive::Button &button)
{
	m_ButtonRenderer.addButton(button);
}

