//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_VERTICALBLURRENDERER_H
#define SURVIVE_VERTICALBLURRENDERER_H


#include <GL/gl.h>

#include "VerticalBlurShader.h"
#include "../../fbo/FrameBuffer.h"

class VerticalBlurRenderer
{
private:
	FrameBuffer m_Fbo;
	VerticalBlurShader m_Shader;

	Texture m_Texture;
	Model m_Model;
	int m_Width, m_Height;

public:
	VerticalBlurRenderer(int targetFboWidth, int targetFboHeight, const Model &model);

	void render() const;

	[[nodiscard]] const Texture &getTexture() const;
};


#endif //SURVIVE_VERTICALBLURRENDERER_H
