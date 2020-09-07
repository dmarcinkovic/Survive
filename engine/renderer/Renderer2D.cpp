//
// Created by david on 27. 03. 2020..
//

#include "Renderer2D.h"

Renderer2D::Renderer2D(Loader &loader)
        : m_Loader(loader)
{

}

void Renderer2D::render() const
{
    m_GuiRenderer.render();
    m_TextRenderer.renderText();

//    m_ButtonRenderer.render();
}

void Renderer2D::addGui(Entity &entity2D) noexcept
{
    m_GuiRenderer.addEntity(entity2D);
}

void Renderer2D::addText(Text &text) noexcept
{
    m_TextRenderer.addText(text, m_Loader);
}

void Renderer2D::addButton(Button &button) noexcept
{
    m_ButtonRenderer.addButton(button);
}

