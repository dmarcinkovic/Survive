#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
        
    while (display.isRunning())
    {
        Display::clearWindow();

        display.update();
    }

    return 0;
}
