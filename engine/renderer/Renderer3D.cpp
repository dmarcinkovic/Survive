//
// Created by david on 22. 05. 2020..
//

#include <iostream>
#include "Renderer3D.h"
#include "../display/Display.h"

Renderer3D::Renderer3D(const Light &light)
        : m_Light(light), m_ObjectRenderer(light), m_ShadowMap(m_ShadowFrameBuffer.attachToDepthBufferTexture()),
          m_AnimationRenderer(light), m_SceneFrameBuffer{}, m_Scene(m_SceneFrameBuffer.createTexture())
{
}

void Renderer3D::render(const Camera &camera) const
{
    m_ShadowFrameBuffer.renderToFrameBuffer(m_ShadowRenderer, camera, m_Light);

    m_ObjectRenderer.render(camera, m_ShadowMap);
    m_TerrainRenderer.render(camera, m_Light, m_ShadowMap);
    m_AnimationRenderer.render(camera);
}

void Renderer3D::add3DObject(Object3D &object3D)
{
    m_ObjectRenderer.add3DObject(object3D);
    m_ShadowRenderer.add3DObject(object3D);
}

void Renderer3D::addTerrain(Terrain &terrain)
{
    m_TerrainRenderer.addTerrain(terrain);
}

void Renderer3D::addAnimatedObject(Object3D &object3D)
{
    m_AnimationRenderer.add3DObject(object3D);
}

void Renderer3D::renderToFbo(const Camera &camera) const
{
	std::cout << "Bind scene\n";
	m_SceneFrameBuffer.bindFrameBuffer();
	Display::clearWindow();

	std::cout << "Bind shadow\n";
	m_ShadowFrameBuffer.renderToFrameBuffer(m_ShadowRenderer, camera, m_Light);

	m_ObjectRenderer.render(camera, m_ShadowMap);
	m_TerrainRenderer.render(camera, m_Light, m_ShadowMap);
	m_AnimationRenderer.render(camera);

	FrameBuffer::unbindFrameBuffer();
}

GLuint Renderer3D::getRenderedTexture() const
{
	return m_Scene;
}
