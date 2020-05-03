//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_RENDERERUTIL_H
#define SURVIVE_RENDERERUTIL_H


#include "../texture/Texture.h"
#include "../shader/Shader.h"

class RendererUtil
{
public:
    static void prepareRendering(const Shader &shader) ;

    static void prepareEntity(const Texture &texture) ;

    static void finishRenderingEntity();

    static void finishRendering();
};


#endif //SURVIVE_RENDERERUTIL_H
