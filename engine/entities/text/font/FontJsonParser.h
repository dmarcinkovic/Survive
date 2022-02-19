//
// Created by david on 19. 12. 2021..
//

#ifndef SURVIVE_FONTJSONPARSER_H
#define SURVIVE_FONTJSONPARSER_H

#include <string>
#include <unordered_map>
#include <regex>
#include <optional>

#include "Character.h"

namespace Survive
{
	class FontJsonParser
	{
	public:
		static void parseFontJson(const std::string &jsonFile, std::unordered_map<int, Character> &characters,
								  float &scaleHeight, float &height);

	private:
		static std::optional<Character> getCharacter(const std::string &line, float scaleW, float scaleH);

		static Character getCharacterFromJsonFile(const std::smatch &result, float scaleW, float scaleH);

		static float getNumber(const std::string &string);
	};
}


#endif //SURVIVE_FONTJSONPARSER_H
