//
// Created by david on 19. 12. 2021..
//

#ifndef SURVIVE_FONTFNTPARSER_H
#define SURVIVE_FONTFNTPARSER_H

#include <string>
#include <unordered_map>

#include "Character.h"

namespace Survive
{
	class FontFntParser
	{
	public:
		static void parseFontFnt(const std::string &fntFile,  std::unordered_map<int, Character> &characters,
								 float &scaleHeight, float &height);

	private:
		static Character getCharacter(const std::vector<std::string> &line, float w, float h);

		static float getNumber(const std::string &string, char delimiter = '=');
	};
}

#endif //SURVIVE_FONTFNTPARSER_H
