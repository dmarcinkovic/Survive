//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUIRENDERER_H
#define SURVIVE_GUIRENDERER_H

#include <functional>
#include <unordered_map>

#include "../entity/Entity2D.h"
#include "GuiShader.h"
#include "../texture/Texture.h"

class GuiRenderer
{
private:
    GuiShader m_Shader{};
    std::unordered_map<Texture, std::vector<Entity2D>, TextureHash> entities;

    void prepareRendering(const Entity2D &entity2D) const;

    static void finishRendering();

public:
    void render();

    void addEntity(const Entity2D &entity2D) noexcept;
};


#endif //SURVIVE_GUIRENDERER_H
