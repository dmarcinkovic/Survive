//
// Created by david on 03. 05. 2020..
//

#include <iostream>
#include "Button.h"
#include "../../display/Display.h"

Button::Button(const Texture &texture, const glm::vec3 &position, float scaleX, float scaleY, const glm::vec4 &color)
        : Entity2D(texture, position, scaleX, scaleY), m_Color(color)
{
    auto mouseListener = [](int button, int action){
        std::cout << "Mouse pressed\n";
        auto[x, y] = Display::getMousePosition();

        std::cout << x << ' ' << y << '\n';
    };

    Display::addMouseListener(mouseListener);
}
