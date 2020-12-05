//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_VERTICALBLUR_H
#define SURVIVE_VERTICALBLUR_H


#include <GL/gl.h>

class VerticalBlur
{
private:
//	ImageRenderer renderer;
//	VerticalBlurShader shader;

public:
	VerticalBlur(int targetFboWidth, int targetFboHeight);

	void render(GLuint texture);

	[[nodiscard]] GLuint getTexture() const;
};


#endif //SURVIVE_VERTICALBLUR_H
