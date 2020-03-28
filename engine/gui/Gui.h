//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUI_H
#define SURVIVE_GUI_H


#include "../renderer/Renderer2D.h"
#include "GuiRenderer.h"

class Gui
{
private:
    GuiRenderer renderer;

public:
    Gui(const char *textureFile, const Renderer2D &renderer2D, Loader &loader);
};


#endif //SURVIVE_GUI_H
