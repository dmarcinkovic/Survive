//
// Created by david on 10. 01. 2021..
//

#ifndef SURVIVE_BLOOMRENDERER_H
#define SURVIVE_BLOOMRENDERER_H

#include "BlurRenderer.h"
#include "HorizontalBlurRenderer.h"
#include "VerticalBlurRenderer.h"

namespace Survive
{
	class BloomRenderer
	{
	private:
		HorizontalBlurRenderer m_HorizontalRenderer;
		VerticalBlurRenderer m_VerticalRenderer;

		Loader m_Loader{};
		Model m_Model;

	public:
		BloomRenderer(int width, int height);

		void render(entt::registry &registry) const;

	private:
		void prepare() const;

		static void finishRendering();
	};
}

#endif //SURVIVE_BLOOMRENDERER_H
