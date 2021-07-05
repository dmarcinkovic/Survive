//
// Created by david on 05. 07. 2021..
//

#ifndef SURVIVE_KEY_H
#define SURVIVE_KEY_H

namespace Survive
{
	enum Key
	{
		GLFW_KEY_SPACE = 32,
		APOSTROPHE = 39,
		COMMA = 44, MINUS, PERIOD, SLASH,
		KEY_0 = 48, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
		SEMICOLON = 59,
		EQUAL = 61,
		A = 65, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		LEFT_BRACKET = 91,
		BACKSLASH = 92,
		RIGHT_BRACKET = 93,
		GRAVE_ACCENT = 96,
		WORLD_1 = 161, WORLD_2 = 162,
		ESCAPE = 256,
		ENTER,
		TAB,
		BACKSPACE,
		INSERT, DELETE,
		RIGHT, LEFT, DOWN, UP,
		PAGE_UP, PAGE_DOWN,
		HOME, END,
		CAPS_LOCK = 280, SCROLL_LOCK, NUM_LOCK,
		PRINT_SCREEN,
		PAUSE,
		F1 = 290, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
	};
}

#endif //SURVIVE_KEY_H
