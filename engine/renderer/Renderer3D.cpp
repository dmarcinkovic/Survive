//
// Created by david on 22. 05. 2020..
//

#include "Renderer3D.h"
#include "../constant/Constants.h"
#include "../display/Display.h"

Renderer3D::Renderer3D(const Light &light)
		: m_Light(light), m_ObjectRenderer(light),
		  m_ShadowMap(m_FrameBuffer.attachToDepthBufferTexture(Constants::SHADOW_WIDTH, Constants::SHADOW_HEIGHT)),
		  m_AnimationRenderer(light)
{
}

void Renderer3D::renderScene(const Camera &camera, const glm::vec4 &plane) const
{
	m_ObjectRenderer.render(camera, m_ShadowMap, plane);
	m_TerrainRenderer.render(camera, m_Light, m_ShadowMap, plane);
	m_AnimationRenderer.render(camera);

	m_SkyRenderer.render(camera);
}

void Renderer3D::render(const Camera &camera) const
{
//	m_MousePicking.render(camera);

	m_FrameBuffer.renderToFrameBuffer(m_ShadowRenderer, camera, m_Light, Constants::SHADOW_WIDTH,
									  Constants::SHADOW_HEIGHT);

	renderToWaterFrameBuffers(camera);
	renderScene(camera);

	m_WaterRenderer.render(camera, m_Light);
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

void Renderer3D::addShadow(Object3D &object)
{
	m_ShadowRenderer.add3DObject(object);
}

void Renderer3D::update()
{
	m_SkyRenderer.rotateSky();
}

void Renderer3D::renderToWaterFrameBuffers(const Camera &camera) const
{
	if (m_WaterRenderer.shouldRender())
	{
		glEnable(GL_CLIP_DISTANCE0);

		renderWaterReflection(camera);
		renderWaterRefraction(camera);

		glDisable(GL_CLIP_DISTANCE0);
	}
}

void Renderer3D::renderWaterReflection(const Camera &camera) const
{
	m_WaterFbo.bindReflectionFrameBuffer();
	Display::clearWindow();
	renderScene(camera, m_ReflectionCLippingPlane);
	WaterFbo::unbindFrameBuffer();
}

void Renderer3D::renderWaterRefraction(const Camera &camera) const
{
	m_WaterFbo.bindRefractionFrameBuffer();
	Display::clearWindow();
	renderScene(camera, m_RefractionCLippingPlane);
	WaterFbo::unbindFrameBuffer();
}

void Renderer3D::addWaterTile(WaterTile &waterTile)
{
	m_WaterRenderer.addWaterTile(waterTile);

	m_ReflectionCLippingPlane = glm::vec4{0, 1, 0, -waterTile.m_Position.y};
	m_RefractionCLippingPlane =  glm::vec4{0, -1, 0, waterTile.m_Position.y};
}

GLuint Renderer3D::getWaterReflectionTexture() const
{
	return m_WaterFbo.reflectionColorTexture();
}

GLuint Renderer3D::getWaterRefractionTexture() const
{
	return m_WaterFbo.refractionColorTexture();
}
