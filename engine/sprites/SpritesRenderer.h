//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESRENDERER_H
#define SURVIVE_SPRITESRENDERER_H


#include "../gui/GuiRenderer.h"
#include "SpritesShader.h"

class SpritesRenderer : public GuiRenderer
{
private:
    SpritesShader m_Shader{};


};


#endif //SURVIVE_SPRITESRENDERER_H
