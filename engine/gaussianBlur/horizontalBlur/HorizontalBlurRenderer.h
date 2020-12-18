//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_HORIZONTALBLURRENDERER_H
#define SURVIVE_HORIZONTALBLURRENDERER_H


#include "../../fbo/FrameBuffer.h"
#include "HorizontalBlurShader.h"

class HorizontalBlurRenderer
{
private:
	FrameBuffer m_Fbo;
	int m_Width, m_Height;

	GLint horizontalBlurTexture;
	HorizontalBlurShader m_Shader;
	Model m_Model;

public:
	HorizontalBlurRenderer(int targetFboWidth, int targetFboHeight, const Model &model);

	void render(const Texture &texture) const;

	[[nodiscard]] GLuint getTexture() const;
};


#endif //SURVIVE_HORIZONTALBLURRENDERER_H
