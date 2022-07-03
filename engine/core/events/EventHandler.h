//
// Created by david on 08. 01. 2021..
//

#ifndef SURVIVE_EVENTHANDLER_H
#define SURVIVE_EVENTHANDLER_H

#include <array>
#include <functional>
#include <GLFW/glfw3.h>

#include "Key.h"

namespace Survive
{
	using KeyListener = std::function<void(int, int)>;
	using MouseListener = std::function<void(int, int, double, double)>;
	using MouseMovedListener = std::function<void(double, double)>;
	using WindowListener = std::function<void(int, int)>;
	using ScrollListener = std::function<void(double, double)>;

	class EventHandler
	{
	private:
		friend class Display;

		static constexpr int NUMBER_OF_KEYS = 350;

		static std::vector<KeyListener> m_KeyEventListeners;
		static std::vector<MouseListener> m_MouseEventListeners;
		static std::vector<MouseMovedListener> m_MouseMoveListeners;
		static std::vector<WindowListener> m_WindowListeners;
		static std::vector<ScrollListener> m_ScrollListeners;

		std::array<bool, NUMBER_OF_KEYS> m_Keys{};

	public:
		EventHandler();

		EventHandler(const EventHandler &eventHandler) = delete;

		[[nodiscard]] bool isKeyPressed(Key key) const;

		[[nodiscard]] bool isKeyControlPressed() const;

		[[nodiscard]] bool isShiftKeyPressed() const;

		static void addKeyListener(const KeyListener &listener);

		static void addMouseListener(const MouseListener &listener);

		static void addScrollListener(const ScrollListener &listener);

		static void addMouseMovedListener(const MouseMovedListener &listener);

		static void addWindowResizeListener(const WindowListener &listener);

		static void popKeyListener();

		static void popMouseListener();

		static void popScrollListener();

		static void popMouseMovedListener();

	private:
		void registerKeyboardListener();

		static void windowResizeCallback(GLFWwindow *window, int width, int height);

		static void keyEventCallback(GLFWwindow *window1, int key, int code, int action, int mods);

		static void mouseEventCallback(GLFWwindow *window, int button, int action, int mods);

		static void mousePositionCallback(GLFWwindow *window, double mouseX, double mouseY);

		static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
	};
}


#endif //SURVIVE_EVENTHANDLER_H
