//
// Created by david on 28. 03. 2020..
//

#ifndef SURVIVE_GUIRENDERER_H
#define SURVIVE_GUIRENDERER_H

#include <unordered_map>

#include "../entity/Entity2D.h"
#include "GuiShader.h"
#include "../texture/Texture.h"

class GuiRenderer
{
private:
    GuiShader m_Shader{};
    std::unordered_map<Texture, std::vector<Entity2D>, TextureHash> m_Entities;

public:
    void render();

    void addEntity(const Entity2D &entity2D) noexcept;

private:
    void prepareRendering() const;

    void prepareEntity(const Texture &texture) const;

    static void finishRenderingEntity();

    static void finishRendering();

};


#endif //SURVIVE_GUIRENDERER_H
