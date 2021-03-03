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
//	m_GuiRenderer.render();

	auto[width, height] = Display::getWindowSize<int>();

	if (width == 0 || height == 0)
	{
		return;
	}

	m_TextRenderer.renderText();
	m_ButtonRenderer.render();
//	m_SpriteRenderer.renderSprite();
}

//void Renderer2D::addGui(Entity &entity2D) noexcept
//{
//	m_GuiRenderer.addEntity(entity2D);
//}

void Renderer2D::addText(Text &text) noexcept
{
	m_TextRenderer.addText(text, m_Loader);
	auto color = text.color();
}

void Renderer2D::addButton(Button &button) noexcept
{
	m_ButtonRenderer.addButton(button);
	addText(button.getText());
}

//void Renderer2D::addSprite(SpriteSheetComponent &sprite) noexcept
//{
//	m_SpriteRenderer.addSprite(sprite);
//}

