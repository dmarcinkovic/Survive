#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/obj/ObjLoader.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;

    ObjLoader::loadObj("res/house.obj");
        
    while (display.isRunning())
    {
        Display::clearWindow();

        display.update();
    }

    return 0;
}
