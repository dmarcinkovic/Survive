//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_RENDERER2D_H
#define SURVIVE_RENDERER2D_H

#include <vector>

#include "../gui/GuiRenderer.h"
#include "../text/TextRenderer.h"
#include "../text/Text.h"

class Renderer2D
{
private:
    const std::vector<float> m_Vertices{-1, -1, 1, -1, 1, 1, -1, 1};
    const std::vector<unsigned> m_Indices{0, 1, 3, 3, 1, 2};
    const Model m_Model;
    Loader &m_Loader;

    GuiRenderer m_GuiRenderer{};
    TextRenderer m_TextRenderer;

public:
    explicit Renderer2D(Loader &loader);

    void render() const;

    void addGui(Entity2D &entity2D) noexcept;

    const Model &getModel() const;

    void addText(Text &text) noexcept;
};

#endif //SURVIVE_RENDERER2D_H
