//
// Created by david on 08. 03. 2020..
//

#ifndef SURVIVE_DISPLAY_H
#define SURVIVE_DISPLAY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Display
{
private:
    GLFWwindow *window;

    static void windowResizeCallback(GLFWwindow *window, int width,int height);

public:
    Display(int width, int height, const char* title);

    ~Display();

    void update();

    static void clearWindow();

    [[nodiscard]] bool isRunning() const;
};


#endif //SURVIVE_DISPLAY_H
