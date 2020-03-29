#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/texture/Texture.h"
#include "engine/renderer/Renderer2D.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 800;

    Display display(width, height, "Survive");

    Loader loader;
    Renderer2D renderer(loader);

    Texture texture2(renderer.getModel(), loader.loadTexture("res/boy.png"));

    Sprite sprite2(texture2, glm::vec3{0.5, 0.5, 0.0}, 0.3, 2, 4);
    renderer.addSprite(sprite2);

    sprite2.animate(6, 1, 0, 1, 3);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
