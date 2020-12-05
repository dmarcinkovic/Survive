//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_HORIZONTALBLURRENDERER_H
#define SURVIVE_HORIZONTALBLURRENDERER_H


#include <GL/glew.h>

class HorizontalBlurRenderer
{
public:
	HorizontalBlurRenderer(int targetFboWidth, int targetFboHeight);

	void render(GLuint texture);

	[[nodiscard]] GLuint getTexture() const;
};


#endif //SURVIVE_HORIZONTALBLURRENDERER_H
