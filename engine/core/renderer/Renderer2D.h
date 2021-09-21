//
// Created by david on 27. 03. 2020..
//

#ifndef SURVIVE_RENDERER2D_H
#define SURVIVE_RENDERER2D_H

#include <vector>

#include "entt.hpp"
#include "button/ButtonRenderer.h"

namespace Survive
{
	class Renderer2D
	{
	private:
		Loader &m_Loader;

		ButtonRenderer m_ButtonRenderer{};

	public:
		explicit Renderer2D(Loader &loader);

		void render(entt::registry &registry) const;

		void addButton(Button &button) noexcept;
	};
}

#endif //SURVIVE_RENDERER2D_H
