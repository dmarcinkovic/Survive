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

class Display
{
private:
    GLFWwindow *m_Window;

    static std::vector<KeyListener> m_KeyEventListeners;
    static std::vector<MouseListener> m_MouseEventListeners;
    static std::vector<MouseMovedListener> m_MouseMoveListeners;
    static std::vector<WindowListener> m_WindowListeners;

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

    static void addMouseMovedListener(const MouseMovedListener &listener);

    static void addWindowResizeListener(const WindowListener &listener);

    static double getFrameTime();

    static std::pair<int, int> getWindowSize();

private:
    static void windowResizeCallback(GLFWwindow *window, int width, int height);

    static void keyEventCallback(GLFWwindow *window1, int key, int code, int action, int mods);

    static void mouseEventCallback(GLFWwindow *window, int button, int action, int mods);

    static void mousePositionCallback(GLFWwindow *window, double mouseX, double mouseY);
};


#endif //SURVIVE_DISPLAY_H
