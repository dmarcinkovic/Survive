//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H

#include "../objects/ObjectRenderer.h"
#include "../terrain/TerrainRenderer.h"
#include "../fbo/FrameBuffer.h"
#include "../animations/renderer/AnimationRenderer.h"
#include "../animations/animation/AnimatedObject.h"
#include "../sky/SkyRenderer.h"
#include "../outline/OutlineRenderer.h"
#include "../mousePicking/MousePicking.h"
#include "../water/WaterRenderer.h"
#include "../water/WaterFbo.h"

class Renderer3D
{
private:
	ObjectRenderer m_ObjectRenderer;
	TerrainRenderer m_TerrainRenderer;
	ShadowRenderer m_ShadowRenderer;
	AnimationRenderer m_AnimationRenderer;
	SkyRenderer m_SkyRenderer;
	OutlineRenderer m_OutlineRenderer;
	MousePicking m_MousePicking;
	WaterRenderer m_WaterRenderer;

	const Light &m_Light;
	FrameBuffer m_FrameBuffer;
	const GLuint m_ShadowMap;
	WaterFbo m_WaterFbo;

	glm::vec4 m_ReflectionCLippingPlane{};
	glm::vec4 m_RefractionCLippingPlane{};

public:
	explicit Renderer3D(const Light &light);

	void render(Camera &camera) const;

	void add3DObject(Object3D &object3D);

	void addTerrain(Terrain &terrain);

	void addAnimatedObject(AnimatedObject &object3D);

	void addSkyboxEntity(const Entity &entity);

	void addOutlineToObject(Object3D &object);

	void removeOutlineToObject();

    void addShadow(Object3D &object);

    void update();

	void renderScene(Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

	void addWaterTile(WaterTile &waterTile);

	// TODO remove this method
	GLuint getWaterReflectionTexture() const;

	// TODO remove this method
	GLuint getWaterRefractionTexture() const;

private:
	void renderToWaterFrameBuffers(Camera &camera) const;

	void renderWaterReflection(Camera &camera) const;

	void renderWaterRefraction(Camera &camera) const;
};


#endif //SURVIVE_RENDERER3D_H
