//
// Created by david on 29. 03. 2020..
//

#include <fstream>
#include "Font.h"

void Font::loadFontFromFntFile(const char *fntFile)
{
    std::ifstream reader(fntFile);

    std::string line;
    while (std::getline(reader, line))
    {
            
    }

    reader.close();
}
