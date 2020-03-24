//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_TEXTURE_H
#define SURVIVE_TEXTURE_H

#include <GL/glew.h>

#include "../renderer/Loader.h"

class Texture
{
private:
    GLuint vao;
    size_t vertexCount;
    GLuint textureId;

public:
    Texture(const Model &model, GLuint textureId);

    void bindTexture();

    static void unbindTexture();
};


#endif //SURVIVE_TEXTURE_H
