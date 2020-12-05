//
// Created by david on 05. 12. 2020..
//

#ifndef SURVIVE_HORIZONTALBLUR_H
#define SURVIVE_HORIZONTALBLUR_H


#include <GL/glew.h>

class HorizontalBlur
{
public:
	HorizontalBlur(int targetFboWidth, int targetFboHeight);

	void render(GLuint texture);

	[[nodiscard]] GLuint getTexture() const;
};


#endif //SURVIVE_HORIZONTALBLUR_H
