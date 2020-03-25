//
// Created by david on 08. 03. 2020..
//

#include "Display.h"

std::vector<Listener> Display::keyEventListeners;
std::vector<Listener> Display::mouseEventListeners;

Display::Display(int width, int height, const char *title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    glewInit();

    glfwSetWindowSizeCallback(m_Window, windowResizeCallback);
    glfwSetMouseButtonCallback(m_Window, mouseEventCallback);
    glfwSetKeyCallback(m_Window, keyEventCallback);
}

Display::~Display()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Display::update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

bool Display::isRunning() const
{
    return !glfwWindowShouldClose(m_Window);
}

void Display::clearWindow()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Display::windowResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, width, 0, height, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Display::keyEventCallback(GLFWwindow *window1, int key, int code, int action, int mods)
{
    for (auto const &listener : keyEventListeners)
    {
        listener(key, action);
    }
}

void Display::mouseEventCallback(GLFWwindow *window, int button, int action, int mods)
{
    for (auto const &listener : mouseEventListeners)
    {
        listener(button, action);
    }
}

void Display::addKeyListener(const Listener &listener)
{
    keyEventListeners.emplace_back(listener);
}

void Display::addMouseListener(const Listener &listener)
{
    mouseEventListeners.emplace_back(listener);
}
