//
// Created by david on 27. 03. 2020..
//

#include "Display.h"
#include "Renderer2D.h"

Survive::Renderer2D::Renderer2D(Loader &loader)
		: m_Loader(loader)
{

}

void Survive::Renderer2D::render(entt::registry &registry) const
{
	m_GuiRenderer.render(registry);

	auto[width, height] = Display::getWindowSize<int>();

	if (width == 0 || height == 0)
	{
		return;
	}

	m_TextRenderer.renderText();
	m_ButtonRenderer.render();
	m_SpriteRenderer.render(registry);
}

void Survive::Renderer2D::addText(Text &text) noexcept
{
	m_TextRenderer.addText(text, m_Loader);
	auto color = text.color();
}

void Survive::Renderer2D::addButton(Button &button) noexcept
{
	m_ButtonRenderer.addButton(button);
	addText(button.getText());
}
