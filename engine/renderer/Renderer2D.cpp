//
// Created by david on 27. 03. 2020..
//

#include "Renderer2D.h"

Renderer2D::Renderer2D(Loader &loader)
        : m_Model(loader.loadToVao(m_Vertices, m_Indices, 2)), m_Loader(loader)
{

}

void Renderer2D::render() const
{
    m_GuiRenderer.render();
    m_TextRenderer.renderText();
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
    m_TextRenderer.addText(text, m_Loader);
}

