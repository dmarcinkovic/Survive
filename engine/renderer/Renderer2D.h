//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_RENDERER2D_H
#define SURVIVE_RENDERER2D_H

#include <vector>

#include "../gui/GuiRenderer.h"
#include "../sprites/SpritesRenderer.h"

class Renderer2D
{
private:
    const std::vector<float> m_Vertices{-1, -1, 1, -1, 1, 1, -1, 1};
    const std::vector<unsigned> m_Indices{0, 1, 3, 3, 1, 2};
    const Model m_Model;

    GuiRenderer m_GuiRenderer{};
    SpritesRenderer m_SpriteRenderer{};

public:
    explicit Renderer2D(Loader &loader);

    void render() const;

    void addGui(const Entity2D &entity2D) noexcept;

    void addSprite(const Entity2D &entity2D) noexcept;

    const Model &getModel() const;
};

#endif //SURVIVE_RENDERER2D_H
