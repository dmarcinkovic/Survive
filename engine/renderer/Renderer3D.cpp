//
// Created by david on 22. 05. 2020..
//

#include "Renderer3D.h"
#include "../constant/Constants.h"

Renderer3D::Renderer3D(const Light &light)
		: m_Light(light), m_ObjectRenderer(light),
		  m_ShadowMap(m_FrameBuffer.attachToDepthBufferTexture(Constants::SHADOW_WIDTH, Constants::SHADOW_HEIGHT)),
		  m_AnimationRenderer(light)
{
}

void Renderer3D::render(const Camera &camera) const
{
	m_MousePicking.render(camera);

	m_FrameBuffer.renderToFrameBuffer(m_ShadowRenderer, camera, m_Light, Constants::SHADOW_WIDTH,
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

void Renderer3D::addShadow(Object3D &object)
{
	m_ShadowRenderer.add3DObject(object);
}
