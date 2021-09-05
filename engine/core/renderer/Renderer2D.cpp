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
	auto[width, height] = Display::getWindowSize<int>();

	if (width == 0 || height == 0)
	{
		return;
	}

	m_TextRenderer.renderText(registry);
	m_ButtonRenderer.render();
}

void Survive::Renderer2D::addButton(Button &button) noexcept
{
	m_ButtonRenderer.addButton(button);
}
