#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/renderer/Renderer2D.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

    TexturedModel texture2(loader.renderQuad(), Loader::loadTexture("res/walking.png"));

    Sprite sprite2(texture2, glm::vec3{0.5, 0.5, 0.0}, 0.3, 1, 8);
    renderer.addSprite(sprite2);

    sprite2.animate(12);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}