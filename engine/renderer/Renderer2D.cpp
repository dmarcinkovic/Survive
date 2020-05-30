//
// Created by david on 27. 03. 2020..
//

#include "Renderer2D.h"
#include "../display/Display.h"

Renderer2D::Renderer2D(Loader &loader)
        : m_Model(loader.loadToVao(m_Vertices, m_Indices, 2)), m_Loader(loader)
{

}

void Renderer2D::render() const
{
    auto[width, height] = Display::getWindowSize();

    if (width == 0 || height == 0)
    {
        return;
    }

//    m_GuiRenderer.render();
//    m_TextRenderer.renderText();

    m_ButtonRenderer.render();
}

void Renderer2D::addGui(Entity2D &entity2D) noexcept
{
    m_GuiRenderer.addEntity(entity2D);
}

const Model &Renderer2D::getModel() const
{
    return m_Model;
}

void Renderer2D::addText(Text &text) noexcept
{
    text.loadTexture(m_Loader);
    m_TextRenderer.addText(text);
}

void Renderer2D::addButton(Button &button) noexcept
{
    m_ButtonRenderer.addButton(button);
}

