//
// Created by david on 08. 03. 2020..
//

#ifndef SURVIVE_DISPLAY_H
#define SURVIVE_DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>

using Listener = std::function<void(int, int)>;

class Display
{
private:
    GLFWwindow *m_Window;

    static std::vector<Listener> keyEventListeners;
    static std::vector<Listener> mouseEventListeners;

    static void windowResizeCallback(GLFWwindow *window, int width, int height);

    static void keyEventCallback(GLFWwindow *window1, int key, int code, int action, int mods);

    static void mouseEventCallback(GLFWwindow *window, int button, int action, int mods);

public:
    Display(int width, int height, const char *title);

    ~Display();

    void update() const;

    static void clearWindow();

    [[nodiscard]] bool isRunning() const;

    static void addKeyListener(const Listener& listener);

    static void addMouseListener(const Listener& listener);
};


#endif //SURVIVE_DISPLAY_H
