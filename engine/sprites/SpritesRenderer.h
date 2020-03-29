//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_SPRITESRENDERER_H
#define SURVIVE_SPRITESRENDERER_H

#include <functional>

#include "../gui/GuiRenderer.h"
#include "SpritesShader.h"
#include "Sprite.h"

class SpritesRenderer : public GuiRenderer
{
private:
    SpritesShader m_Shader{};
    std::unordered_map<Texture, std::vector<std::reference_wrapper<Sprite>>, TextureHash> m_Sprites;

public:
    void renderSprite() const;

    void addSprite(Sprite &sprite) noexcept;

private:
    void animate(Sprite &sprite) const;
};


#endif //SURVIVE_SPRITESRENDERER_H
