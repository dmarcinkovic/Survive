//
// Created by david on 29. 03. 2020..
//

#include <fstream>

#include "Font.h"
#include "../util/Util.h"

void Font::loadFontFromFntFile(const char *fntFile)
{
    std::ifstream reader(fntFile);

    float w = 0, h = 0;

    std::string line;
    while (std::getline(reader, line))
    {
        auto result = Util::split(line, R"([^\s+]+)");
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

void Font::loadFontFromJsonFile(const char *jsonFile)
{
    std::ifstream reader(jsonFile);

    float w = 1039, h = 350; // TODO do not hard code this

    std::string line;
    while (std::getline(reader, line))
    {
        Character c = Util::getCharacterFromJsonFile(line, w, h);
        if (c.m_ScaleW != 0)
        {
            m_Characters.insert({c.m_Id, c});
        }
    }

    reader.close();
}

const Character &Font::getCharacter(int ascii) const
{
    return m_Characters.at(ascii);
}
