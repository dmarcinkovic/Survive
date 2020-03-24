
#include "engine/display/Display.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height,"Survive");

    while (display.isRunning())
    {
        Display::clearWindow();



        display.update();
    }

    return 0;
}
