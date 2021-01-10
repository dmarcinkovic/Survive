//
// Created by david on 08. 03. 2020..
//

#ifndef SURVIVE_DISPLAY_H
#define SURVIVE_DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

using KeyListener = std::function<void(int, int)>;
using MouseListener = std::function<void(int, int, double, double)>;
using MouseMovedListener = std::function<void(double, double)>;
using WindowListener = std::function<void(int, int)>;
using ScrollListener = std::function<void(double, double)>;

class Display
{
private:
	GLFWwindow *m_Window;

	static std::vector<KeyListener> m_KeyEventListeners;
	static std::vector<MouseListener> m_MouseEventListeners;
	static std::vector<MouseMovedListener> m_MouseMoveListeners;
	static std::vector<WindowListener> m_WindowListeners;
	static std::vector<ScrollListener> m_ScrollListeners;

	static double m_LastFrameTime;
	static double m_DeltaTime;

	static int m_Width, m_Height;

public:
	Display(int width, int height, const char *title);

	~Display();

	void update() const;

	static void clearWindow();

	[[nodiscard]] bool isRunning() const;

	static void addKeyListener(const KeyListener &listener);

	static void addMouseListener(const MouseListener &listener);

	static void addScrollListener(const ScrollListener &listener);

	static void addMouseMovedListener(const MouseMovedListener &listener);

	static void addWindowResizeListener(const WindowListener &listener);

	static double getFrameTime();

	template<typename T>
	static std::pair<T, T> getWindowSize()
	{
		return {static_cast<T>(m_Width), static_cast<T>(m_Height)};
	}

	static int getWidth();

	static int getHeight();

private:
	static void windowResizeCallback(GLFWwindow *window, int width, int height);

	static void keyEventCallback(GLFWwindow *window1, int key, int code, int action, int mods);

	static void mouseEventCallback(GLFWwindow *window, int button, int action, int mods);

	static void mousePositionCallback(GLFWwindow *window, double mouseX, double mouseY);

	static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

	void addCallbacks() const;

	static void setProjectionMatrices(int width, int height);

	static void setViewport(int width, int height);

	static void setWindowHints();

	static void setStencilProperties();
};


#endif //SURVIVE_DISPLAY_H
