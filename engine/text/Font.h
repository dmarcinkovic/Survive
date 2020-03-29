//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_FONT_H
#define SURVIVE_FONT_H


#include <vector>
#include "Character.h"

class Font
{
private:
    std::vector<Character> m_Characters;

public:
    void loadFontFromFntFile(const char* fntFile);
};


#endif //SURVIVE_FONT_H
