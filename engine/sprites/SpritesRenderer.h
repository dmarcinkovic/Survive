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
    std::unordered_map<Texture, std::vector<Entity2D>, TextureHash> m_Sprites;

public:
    void renderSprite() const;

    void addSprite(const Entity2D &entity2D) noexcept;
};


#endif //SURVIVE_SPRITESRENDERER_H
