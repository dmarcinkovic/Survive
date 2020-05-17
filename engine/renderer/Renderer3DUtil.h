//
// Created by david on 17. 05. 2020..
//

#ifndef SURVIVE_RENDERER3DUTIL_H
#define SURVIVE_RENDERER3DUTIL_H


#include "../shader/Shader.h"
#include "../texture/Texture.h"

class Renderer3DUtil
{
public:
    static void prepareRendering(const Shader &shader, bool cullFace, bool blend);

    static void finishRendering();

    static void prepareEntity(const Texture &texture);

    static void finishRenderingEntity();
};


#endif //SURVIVE_RENDERER3DUTIL_H
