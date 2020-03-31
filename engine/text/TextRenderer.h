//
// Created by david on 29. 03. 2020..
//

#ifndef SURVIVE_TEXTRENDERER_H
#define SURVIVE_TEXTRENDERER_H

#include "../gui/GuiRenderer.h"
#include "TextShader.h"
#include "Text.h"

class TextRenderer : public GuiRenderer
{
private:
    TextShader m_Shader{};
    std::unordered_map<Texture, std::vector<std::reference_wrapper<Text>>, TextureHash> m_Texts;

public:
    void renderText() const;

    void addText(Text &text);
};


#endif //SURVIVE_TEXTRENDERER_H
