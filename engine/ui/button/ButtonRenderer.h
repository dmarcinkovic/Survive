//
// Created by david on 05. 05. 2020..
//

#ifndef SURVIVE_BUTTONRENDERER_H
#define SURVIVE_BUTTONRENDERER_H

#include <functional>
#include <vector>

#include "ButtonShader.h"
#include "../../texture/Texture.h"
#include "Button.h"

class ButtonRenderer
{
private:
    ButtonShader m_Shader{};
    std::vector<std::reference_wrapper<Button>> m_Buttons;

public:
    void render() const;

    void addButton(Button &button) noexcept;
};


#endif //SURVIVE_BUTTONRENDERER_H
