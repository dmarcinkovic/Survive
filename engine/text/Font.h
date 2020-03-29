//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_FONT_H
#define SURVIVE_FONT_H

#include <unordered_map>

#include "Character.h"

class Font
{
private:
    std::unordered_map<int, Character> m_Characters;

public:
    void loadFontFromFntFile(const char* fntFile);

    const Character &getCharacter(int ascii) const;
};


#endif //SURVIVE_FONT_H
