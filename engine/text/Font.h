//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_FONT_H
#define SURVIVE_FONT_H

#include <unordered_map>

#include "Character.h"
#include "../renderer/Loader.h"

class Font
{
private:
    std::unordered_map<int, Character> m_Characters;
    GLuint m_TextureId{};

public:
    Font(const char* textureAtlas, Loader &loader);

    Font() = default;

    void loadFontFromFntFile(const char* fntFile);

    void loadFontFromJsonFile(const char* jsonFile);

    const Character &getCharacter(int ascii) const;

    GLuint getMTextureId() const;
};



#endif //SURVIVE_FONT_H
