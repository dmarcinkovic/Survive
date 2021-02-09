//
// Created by david on 22. 05. 2020..
//

#include "Renderer3D.h"
#include "../constant/Constants.h"
#include "../display/Display.h"

Renderer3D::Renderer3D(const Light &light)
		: m_Light(light), m_ObjectRenderer(light),
		  m_ShadowMap(
				  m_ShadowFrameBuffer.attachToDepthBufferTexture(Constants::SHADOW_WIDTH, Constants::SHADOW_HEIGHT)),
		  m_AnimationRenderer(light), m_SceneSize(Display::getWindowSize<int>())
{
	m_Scene = m_SceneFrameBuffer.createTexture(m_SceneSize.first, m_SceneSize.second);
}

void Renderer3D::render(const Camera &camera) const
{

	m_MousePicking.render(camera);
	m_ShadowFrameBuffer.renderToFrameBuffer(m_ShadowRenderer, camera, m_Light, Constants::SHADOW_WIDTH,
											Constants::SHADOW_HEIGHT);

	m_ObjectRenderer.render(camera, m_ShadowMap);
	m_TerrainRenderer.render(camera, m_Light, m_ShadowMap);
	m_AnimationRenderer.render(camera);

	m_SkyRenderer.render(camera);
	m_OutlineRenderer.render(camera);
}

void Renderer3D::add3DObject(Object3D &object3D)
{
	m_ObjectRenderer.add3DObject(object3D);
	m_MousePicking.add3DObject(object3D);
}

void Renderer3D::addTerrain(Terrain &terrain)
{
	m_TerrainRenderer.addTerrain(terrain);
}

void Renderer3D::addAnimatedObject(AnimatedObject &object3D)
{
	m_AnimationRenderer.addAnimatedModel(object3D);
}

void Renderer3D::addSkyboxEntity(const Entity &entity)
{
	m_SkyRenderer.addSkyEntity(entity);
}

void Renderer3D::addOutlineToObject(Object3D &object)
{
	m_OutlineRenderer.add3DObject(object);
}

void Renderer3D::removeOutlineToObject()
{
	m_OutlineRenderer.removeObject();
}

void Renderer3D::renderToFbo(const Camera &camera) const
{
	m_ShadowFrameBuffer.renderToFrameBuffer(m_ShadowRenderer, camera, m_Light, Constants::SHADOW_WIDTH,
											Constants::SHADOW_HEIGHT);

	glViewport(0, 0, m_SceneSize.first, m_SceneSize.second);

	m_SceneFrameBuffer.bindFrameBuffer();
	Display::clearWindow();

	m_ObjectRenderer.render(camera, m_ShadowMap);
	m_TerrainRenderer.render(camera, m_Light, m_ShadowMap);
	m_AnimationRenderer.render(camera);
	m_SkyRenderer.render(camera);

	FrameBuffer::unbindFrameBuffer();

	resetViewport();
}

GLuint Renderer3D::getRenderedTexture() const
{
	return m_Scene;
}

void Renderer3D::addShadow(Object3D &object)
{
	m_ShadowRenderer.add3DObject(object);
}

void Renderer3D::resetViewport()
{
	auto[width, height] = Display::getWindowSize<int>();
	glViewport(0, 0, width, height);
}
