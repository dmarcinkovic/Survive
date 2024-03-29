//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_HORIZONTALBLURRENDERER_H
#define SURVIVE_HORIZONTALBLURRENDERER_H


#include "HorizontalBlurShader.h"
#include "FrameBuffer.h"

namespace Survive
{
	class HorizontalBlurRenderer
	{
	private:
		FrameBuffer m_Fbo;
		int m_Width, m_Height;

		Texture m_HorizontalBlurTexture;
		HorizontalBlurShader m_Shader;

	public:
		HorizontalBlurRenderer(int targetFboWidth, int targetFboHeight);

		void render(const Texture &texture, const Model &model) const;

		[[nodiscard]] const Texture &getTexture() const;
	};
}

#endif //SURVIVE_HORIZONTALBLURRENDERER_H
