//
// Created by david on 08. 03. 2020..
//

#include "Display.h"

Display::Display(int width, int height, const char *title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewInit();
}

Display::~Display()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Display::update()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

bool Display::isRunning() const
{
    return !glfwWindowShouldClose(window);
}

void Display::clearWindow()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
