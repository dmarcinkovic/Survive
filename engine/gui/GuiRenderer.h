//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUIRENDERER_H
#define SURVIVE_GUIRENDERER_H


#include "../entity/Entity2D.h"
#include "GuiShader.h"

class GuiRenderer
{
private:
    GuiShader m_Shader{};

    void prepareRendering(const Entity2D &entity2D) const;

    static void finishRendering();

public:
    void render(const Entity2D &entity2D);
};


#endif //SURVIVE_GUIRENDERER_H
