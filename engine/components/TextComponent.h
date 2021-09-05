//
// Created by david on 05. 09. 2021..
//

#ifndef SURVIVE_TEXTCOMPONENT_H
#define SURVIVE_TEXTCOMPONENT_H

#include "Text.h"

namespace Survive
{
	struct TextComponent
	{
		Text text;

		TextComponent() = default;

		TextComponent(const std::string& string, const Font& font)
			: text(string, font)
		{}
	};
}

#endif //SURVIVE_TEXTCOMPONENT_H
