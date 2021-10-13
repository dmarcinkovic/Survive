//
// Created by david on 22. 05. 2020..
//

#ifndef SURVIVE_RENDERER_H
#define SURVIVE_RENDERER_H

#include "TextRenderer.h"
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
	class Renderer
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
		TextRenderer m_TextRenderer{};

		const Light &m_Light;
		FrameBuffer m_ShadowFrameBuffer;
		const GLuint m_ShadowMap;

		std::pair<int, int> m_SceneSize;

		FrameBuffer m_SceneFrameBuffer;
		GLuint m_Scene{};
		glm::vec4 m_ReflectionCLippingPlane{};
		glm::vec4 m_RefractionCLippingPlane{};

	public:
		explicit Renderer(const Light &light);

		void render(entt::registry &registry, Camera &camera) const;

		void renderEditor(entt::registry &registry, Camera &camera) const;

		void renderApp(entt::registry &registry, Camera &camera) const;

		void addSkyboxEntity(entt::entity sky);

		void removeSkyboxEntity();

		void addOutlineToObject(entt::registry &registry, entt::entity entity);

		[[nodiscard]] GLuint getRenderedTexture() const;

		void removeOutlineToObject(entt::registry &registry);

		void render3DScene(entt::registry &registry, const Camera &camera, const glm::vec4 &plane = glm::vec4{}) const;

		void render2DScene(entt::registry &registry, const Camera &camera) const;

		void setMousePickingPosition(float mouseX, float mouseY);

		void addMousePickingListener(const MousePickingListener &listener);

		void popMousePickingListener();

	private:
		void renderScene(entt::registry &registry, Camera &camera, bool renderEditor) const;

		void renderToWaterFrameBuffers(entt::registry &registry, Camera &camera) const;

		static void resetViewport();

		void renderWaterReflection(entt::registry &registry, Camera &camera) const;

		void renderWaterRefraction(entt::registry &registry, const Camera &camera) const;
	};
}

#endif //SURVIVE_RENDERER_H
