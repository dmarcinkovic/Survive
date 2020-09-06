//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXTRENDERER_H
#define SURVIVE_TEXTRENDERER_H

#include "TextShader.h"
#include "Text.h"

#include <functional>

class TextRenderer
{
private:
    TextShader m_Shader{};
    std::unordered_map<TexturedModel, std::vector<std::reference_wrapper<Text>>, TextureHash> m_Texts;

public:
    void renderText() const;

    void addText(Text &text);
};


#endif //SURVIVE_TEXTRENDERER_H
