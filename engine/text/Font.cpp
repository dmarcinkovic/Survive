//
// Created by david on 29. 03. 2020..
//

#include <fstream>

#include "Font.h"
#include "../util/Util.h"

Survive::Font::Font(const char *textureAtlas, Loader &loader)
		: m_FontTexture(Loader::loadTexture(textureAtlas))
{
}

void Survive::Font::loadFontFromFntFile(const char *fntFile)
{
	std::ifstream reader(fntFile);

	float w = 0, h = 0;

	std::string line;
	while (std::getline(reader, line))
	{
		auto result = Util::splitByRegex(line);
		if (!result.empty() && result[0] == "char")
		{
			Character c = Util::getCharacterFromFntFile(result, w, h);
			m_Characters.insert({c.m_Id, c});
		} else if (!result.empty() && result[0] == "common")
		{
			w = Util::getNumber(result[3]);
			h = Util::getNumber(result[4]);
		}
	}

	reader.close();
}

void Survive::Font::loadFontFromJsonFile(const char *jsonFile)
{
	std::ifstream reader(jsonFile);

	float scaleW = 0, scaleH = 0;

	std::string line;
	while (std::getline(reader, line))
	{
		auto c = Util::getCharacterFromJsonFile(line, scaleW, scaleH);
		if (c)
		{
			m_Characters.insert({c.value().m_Id, c.value()});
		} else if (line.find("width") != -1)
		{
			scaleW = Util::getNumber(line, ':');
		} else if (line.find("height") != -1)
		{
			scaleH = Util::getNumber(line, ':');
		}
	}

	reader.close();
}

const Survive::Character &Survive::Font::getCharacter(int ascii) const
{
	return m_Characters.at(ascii);
}

const Survive::Texture &Survive::Font::getTexture() const
{
	return m_FontTexture;
}
