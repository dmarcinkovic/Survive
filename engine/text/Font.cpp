//
// Created by david on 29. 03. 2020..
//

#include <fstream>

#include "Font.h"
#include "../util/Util.h"

void Font::loadFontFromFntFile(const char *fntFile)
{
    std::ifstream reader(fntFile);

    std::string line;
    while (std::getline(reader, line))
    {
        auto result = Util::split(line, R"([^\s+]+)");
        if (!result.empty() && result[0] == "char")
        {
            Character c = Util::getCharacter(result);
            m_Characters.insert({c.m_Id, c});
        }
    }

    reader.close();
}
