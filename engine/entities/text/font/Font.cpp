//
// Created by david on 29. 03. 2020..
//

#include "Font.h"

#include "FontJsonParser.h"
#include "FontFntParser.h"

Survive::Font::Font(const char *textureAtlas, Loader &loader)
		: m_FontTexture(loader.loadTexture(textureAtlas))
{
}

void Survive::Font::loadFontFromFntFile(const std::string &fntFile)
try
{
	FontFntParser::parseFontFnt(fntFile, m_Characters, m_ScaleHeight, m_Height);
	m_Loaded = true;
} catch (const std::exception &ignorable)
{
}

void Survive::Font::loadFontFromJsonFile(const std::string &jsonFile)
try
{
	FontJsonParser::parseFontJson(jsonFile, m_Characters, m_ScaleHeight, m_Height);
	m_Loaded = true;
} catch (const std::exception &ignorable)
{
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
