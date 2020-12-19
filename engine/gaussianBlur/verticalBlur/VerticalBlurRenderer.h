//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_VERTICALBLURRENDERER_H
#define SURVIVE_VERTICALBLURRENDERER_H


#include "VerticalBlurShader.h"
#include "../../fbo/FrameBuffer.h"

class VerticalBlurRenderer
{
private:
	FrameBuffer m_Fbo;
	int m_Width, m_Height;

	VerticalBlurShader m_Shader;
	Texture m_VerticalBlurTexture;

public:
	VerticalBlurRenderer(int targetFboWidth, int targetFboHeight);

	void render(const Texture &texture) const;

	[[nodiscard]] const Texture &getTexture() const;
};


#endif //SURVIVE_VERTICALBLURRENDERER_H
