//
// Created by david on 29. 12. 2020..
//

#include <iostream>

#include "MousePicking.h"
#include "../display/Display.h"

MousePicking::MousePicking()
{
	mousePressedHandler();
}

void MousePicking::mousePressedHandler()
{
	Display::addMouseListener([this](int button, int action, double mouseX, double mouseY){
		std::cout << "Mouse pressed: " << mouseX << ' ' << mouseY << '\n';
	});
}
