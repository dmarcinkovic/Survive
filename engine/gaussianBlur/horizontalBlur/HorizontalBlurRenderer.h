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
	HorizontalBlurShader m_Shader;

	Texture m_Texture;
	Model m_Model;
	int m_Width, m_Height;

public:
	HorizontalBlurRenderer(int targetFboWidth, int targetFboHeight, const Model &model);

	void render() const;

	[[nodiscard]] const Texture &getTexture() const;
};


#endif //SURVIVE_HORIZONTALBLURRENDERER_H
