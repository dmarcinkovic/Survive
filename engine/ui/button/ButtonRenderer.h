//
// Created by david on 03. 05. 2020..
//

#ifndef SURVIVE_BUTTONRENDERER_H
#define SURVIVE_BUTTONRENDERER_H


#include <vector>
#include <functional>

#include "ButtonShader.h"
#include "Button.h"

class ButtonRenderer
{
private:
    ButtonShader m_Shader{};

    std::vector<std::reference_wrapper<Button>> m_Buttons;

public:
    void render() const;

    void addButton(Button &button);
};


#endif //SURVIVE_BUTTONRENDERER_H
