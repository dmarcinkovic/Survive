//
// Created by david on 24. 03. 2020..
//

#ifndef SURVIVE_TEXTURE_H
#define SURVIVE_TEXTURE_H


#include <GL/glew.h>

struct Texture
{
    GLuint vao;
    size_t vertexCount;
    GLuint textureId;

    Texture(GLuint vao, GLuint textureId, size_t vertexCount);
};


#endif //SURVIVE_TEXTURE_H
