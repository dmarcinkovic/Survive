//
// Created by david on 05. 09. 2021..
//

#ifndef SURVIVE_TEXTCOMPONENT_H
#define SURVIVE_TEXTCOMPONENT_H

#include <utility>

#include "Text.h"

namespace Survive
{
	struct TextComponent
	{
		Text text;

		std::string fontFile;
		std::string textureAtlas;

		TextComponent() = default;

		TextComponent(const std::string& string, const Font& font)
			: text(string, font)
		{}

		explicit TextComponent(Text text)
			: text(std::move(text))
		{}
	};
}

#endif //SURVIVE_TEXTCOMPONENT_H
