//
// Created by david on 27. 03. 2020..
//

#include "Renderer2D.h"

Renderer2D::Renderer2D(Loader &loader)
    : m_Model(loader.loadToVao(m_Vertices,m_Indices,2))
{

}

void Renderer2D::render() const
{
    m_GuiRenderer.renderGui();
    m_SpriteRenderer.renderSprite();
}

void Renderer2D::addGui(const Entity2D &entity2D) noexcept
{
    m_GuiRenderer.addGui(entity2D);
}

const Model &Renderer2D::getModel() const
{
    return m_Model;
}

void Renderer2D::addSprite(const Entity2D &entity2D) noexcept
{
    m_SpriteRenderer.addSprite(entity2D);
}

