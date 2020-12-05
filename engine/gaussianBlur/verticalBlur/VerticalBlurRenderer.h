//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_VERTICALBLURRENDERER_H
#define SURVIVE_VERTICALBLURRENDERER_H


#include <GL/gl.h>

class VerticalBlurRenderer
{
private:
//	ImageRenderer renderer;
//	VerticalBlurShader shader;

public:
	VerticalBlurRenderer(int targetFboWidth, int targetFboHeight);

	void render(GLuint texture);

	[[nodiscard]] GLuint getTexture() const;
};


#endif //SURVIVE_VERTICALBLURRENDERER_H
