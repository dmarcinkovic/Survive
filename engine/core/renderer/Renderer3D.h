//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_RENDERER3D_H
#define SURVIVE_RENDERER3D_H

#include "GuiRenderer.h"
#include "SpritesRenderer.h"
#include "AnimationRenderer.h"
#include "WaterRenderer.h"
#include "TerrainRenderer.h"
#include "SkyRenderer.h"
#include "ObjectRenderer.h"
#include "MousePicking.h"
#include "OutlineRenderer.h"
#include "BloomRenderer.h"

namespace Survive
{
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
		BloomRenderer m_BloomRenderer;
		SpritesRenderer m_SpriteRenderer{};
		GuiRenderer m_GuiRenderer{};

		const Light &m_Light;
		FrameBuffer m_ShadowFrameBuffer;
		const GLuint m_ShadowMap;

		std::pair<int, int> m_SceneSize;

		FrameBuffer m_SceneFrameBuffer;
		GLuint m_Scene{};
		glm::vec4 m_ReflectionCLippingPlane{};
		glm::vec4 m_RefractionCLippingPlane{};

	public:
		explicit Renderer3D(const Light &light);

		void render(entt::registry &registry, Camera &camera) const;

		void renderToFbo(entt::registry &registry, Camera &camera) const;

		void addSkyboxEntity(entt::entity sky);

		void addOutlineToObject(entt::registry &registry, entt::entity entity);

		GLuint getRenderedTexture() const;

		void removeOutlineToObject(entt::registry &registry);

		void addShadow(entt::registry &registry, entt::entity entity);

		void render3DScene(entt::registry &registry, Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

		void render2DScene(entt::registry &registry) const;

	private:
		void renderToWaterFrameBuffers(entt::registry &registry, Camera &camera) const;

		static void resetViewport();

		void renderWaterReflection(entt::registry &registry, Camera &camera) const;

		void renderWaterRefraction(entt::registry &registry, Camera &camera) const;
	};
}

#endif //SURVIVE_RENDERER3D_H
