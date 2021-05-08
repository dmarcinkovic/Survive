//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_RENDERER2D_H
#define SURVIVE_RENDERER2D_H

#include <vector>

#include "SpritesRenderer.h"
#include "GuiRenderer.h"
#include "Text.h"
#include "TextRenderer.h"
#include "button/ButtonRenderer.h"

namespace Survive
{
	class Renderer2D
	{
	private:
		Loader &m_Loader;

		GuiRenderer m_GuiRenderer{};
		TextRenderer m_TextRenderer;
		ButtonRenderer m_ButtonRenderer{};
		SpritesRenderer m_SpriteRenderer{};

	public:
		explicit Renderer2D(Loader &loader);

		void render(entt::registry &registry) const;

		void addText(Text &text) noexcept;

		void addButton(Button &button) noexcept;
	};
}

#endif //SURVIVE_RENDERER2D_H
