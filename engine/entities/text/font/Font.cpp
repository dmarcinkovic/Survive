//
// Created by david on 29. 03. 2020..
//

#include <fstream>

#include "Font.h"
#include "Util.h"
#include "Log.h"
#include "FontJsonParser.h"

Survive::Font::Font(const char *textureAtlas, Loader &loader)
		: m_FontTexture(loader.loadTexture(textureAtlas))
{
}

void Survive::Font::loadFontFromFntFile(const std::string &fntFile)
{
	std::ifstream reader(fntFile);

	if (!reader)
	{
		Log::logWindow(LogType::ERROR, "Cannot load font");
		return;
	}

	float w = 0;

	std::string line;
	while (std::getline(reader, line))
	{
		auto result = Util::splitByRegex(line);
		if (!result.empty() && result[0] == "char")
		{
			Character c = Util::getCharacterFromFntFile(result, w, m_ScaleHeight);
			m_Characters.insert({c.m_Id, c});
		} else if (!result.empty() && result[0] == "common")
		{
			w = Util::getNumber(result[3]);

			m_ScaleHeight = Util::getNumber(result[4]);
			m_Height = Util::getNumber(result[1]);
		}
	}

	m_Loaded = true;
	reader.close();
}

void Survive::Font::loadFontFromJsonFile(const std::string &jsonFile)
{
	try
	{
		FontJsonParser::parseFontJson(jsonFile, m_Characters, m_ScaleHeight, m_Height);
		m_Loaded = true;
	} catch(const std::exception &exception)
	{
		Log::logWindow(LogType::ERROR, "Cannot load font");
	}
}

const Survive::Character &Survive::Font::getCharacter(int ascii) const
{
	return m_Characters.at(ascii);
}

const Survive::Texture &Survive::Font::getTexture() const
{
	return m_FontTexture;
}

void Survive::Font::setTexture(const Texture &fontTexture)
{
	m_FontTexture = fontTexture;
}

bool Survive::Font::isFontLoaded() const
{
	return m_Loaded;
}

float Survive::Font::getHeight() const
{
	return m_Height;
}

float Survive::Font::getScaleHeight() const
{
	return m_ScaleHeight;
}

bool Survive::Font::isFontTextureValid() const
{
	return m_FontTexture.isValidTexture();
}
