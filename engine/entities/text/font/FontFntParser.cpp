//
// Created by david on 19. 12. 2021..
//

#include <fstream>

#include "FontFntParser.h"
#include "Util.h"

void Survive::FontFntParser::parseFontFnt(const std::string &fntFile, std::unordered_map<int, Character> &characters,
										  float &scaleHeight, float &height)
{
	std::ifstream reader(fntFile);

	if (!reader)
	{
		throw std::runtime_error("Cannot load font");
	}

	float w = 0;

	std::string line;
	while (std::getline(reader, line))
	{
		auto result = Util::splitByRegex(line);
		if (!result.empty() && result[0] == "char")
		{
			Character c = getCharacter(result, w, scaleHeight);
			characters.insert({c.m_Id, c});
		} else if (!result.empty() && result[0] == "common")
		{
			w = getNumber(result[3]);

			scaleHeight = getNumber(result[4]);
			height = getNumber(result[1]);
		}
	}

	reader.close();
}

Survive::Character
Survive::FontFntParser::getCharacter(const std::vector<std::string> &line, float w, float h)
{
	int id = std::floor(getNumber(line[1]));
	float x = getNumber(line[2]);
	float y = getNumber(line[3]);
	float width = getNumber(line[4]);
	float height = getNumber(line[5]);
	float xOffset = getNumber(line[6]);
	float yOffset = -getNumber(line[7]);
	float advance = getNumber(line[8]);

	return {id, x, y, width, height, xOffset, yOffset, advance, w, h};
}

float Survive::FontFntParser::getNumber(const std::string &string)
{
	unsigned int index = string.find('=');
	return std::stof(string.substr(index + 1));
}
