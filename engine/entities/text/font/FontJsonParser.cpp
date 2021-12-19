//
// Created by david on 19. 12. 2021..
//

#include <fstream>
#include <regex>

#include "FontJsonParser.h"

void
Survive::FontJsonParser::parseFontJson(const std::string &jsonFile, std::unordered_map<int, Character> &characters,
									   float &scaleHeight, float &height)
{
	std::ifstream reader(jsonFile);

	if (!reader)
	{
		throw std::runtime_error("Cannot load font");
	}

	float scaleW = 0;

	std::string line;
	while (std::getline(reader, line))
	{
		auto c = getCharacter(line, scaleW, scaleHeight);
		if (c)
		{
			characters.insert({c.value().m_Id, c.value()});
		} else if (line.find("width") != -1)
		{
			scaleW = getNumber(line);
		} else if (line.find("height") != -1)
		{
			scaleHeight = getNumber(line);
		} else if (line.find("size") != -1)
		{
			height = getNumber(line);
		}
	}

	reader.close();
}

std::optional<Survive::Character> Survive::FontJsonParser::getCharacter(const std::string &line, float scaleW, float scaleH)
{
	static std::string pattern = R"(\s+\"(.?.?)\":\{\"x\":(\d+),\"y\":(\d+),\"width\":(\d+),\"height\")"
								 R"(:(\d+),\"originX\":(-?\d+),\"originY\":(-?\d+),\"advance\":(\d+))";
	static std::regex regex(pattern);
	std::smatch result;
	std::regex_search(line, result, regex);

	if (result.empty())
	{
		return {};
	}

	return getCharacterFromJsonFile(result, scaleW, scaleH);
}

Survive::Character
Survive::FontJsonParser::getCharacterFromJsonFile(const std::smatch &result, float scaleW, float scaleH)
{
	int id = result[1].str().length() == 2 ? result[1].str()[1] : result[1].str()[0];
	float x = std::stof(result[2].str());
	float y = std::stof(result[3].str());
	float width = std::stof(result[4].str());
	float height = std::stof(result[5].str());
	float xOffset = std::stof(result[6].str());
	float yOffset = std::stof(result[7].str());
	float advance = std::stof(result[8].str());

	return {id, x, y, width, height, xOffset, yOffset, advance, scaleW, scaleH};
}

float Survive::FontJsonParser::getNumber(const std::string &string)
{
	unsigned int index = string.find(':');
	return std::stof(string.substr(index + 1));
}
