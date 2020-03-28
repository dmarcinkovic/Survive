//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUI_H
#define SURVIVE_GUI_H

#include <glm/vec3.hpp>

#include "../renderer/Renderer2D.h"
#include "../renderer/Loader.h"
#include "GuiRenderer.h"

class Gui
{
public:
    Gui(Renderer2D &renderer2D, Loader &loader, const char *texture, const glm::vec3 &position, float scale = 1.0f);
};


#endif //SURVIVE_GUI_H
