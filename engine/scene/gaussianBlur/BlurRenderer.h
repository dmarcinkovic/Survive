//
// Created by david on 19. 12. 2020..
//

#ifndef SURVIVE_BLURRENDERER_H
#define SURVIVE_BLURRENDERER_H

#include <functional>
#include <unordered_map>

#include "entt.hpp"
#include "AnimationRenderer.h"
#include "TerrainRenderer.h"
#include "ObjectRenderer.h"
#include "verticalBlur/VerticalBlurRenderer.h"
#include "horizontalBlur/HorizontalBlurRenderer.h"

namespace Survive
{
	class BlurRenderer
	{
	private:
		AnimationRenderer m_AnimationRenderer;
		ObjectRenderer m_ObjectRenderer;
		TerrainRenderer m_TerrainRenderer;

		Loader m_Loader{};
		FrameBuffer m_Fbo{};
		Model m_Model;
		const Light &m_Light;

		int m_Width, m_Height;

		Texture m_Texture;
		HorizontalBlurRenderer m_HorizontalBlurRenderer;
		VerticalBlurRenderer m_VerticalBlurRenderer;

	public:
		BlurRenderer(const Light &light, int width, int height);

		void render(entt::registry &registry, const Camera &camera) const;

		[[nodiscard]] const Texture &getTexture() const;

	private:
		void renderToFbo(entt::registry &registry, const Camera &camera) const;

		void renderBlur() const;

		void prepareRendering() const;

		static void finishRendering();
	};
}


#endif //SURVIVE_BLURRENDERER_H
