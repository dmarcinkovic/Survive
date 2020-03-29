#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"
#include "engine/text/Font.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

    Font font;
    font.loadFontFromFntFile("res/arial.fnt");

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
