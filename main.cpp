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

    Texture texture2(renderer.getModel(), loader.loadTexture("res/walking.png"));

    float x = 0.0;
    Sprite sprite2(texture2, glm::vec3{x, 0.5, 0.0}, 0.3, 1, 8);
    renderer.addSprite(sprite2);

    sprite2.animate(10);

    while (display.isRunning())
    {
        Display::clearWindow();

        x += 0.01;
        if (x >= 1.2)
        {
            x = -1.2;
        }
        sprite2.m_Position = glm::vec3{x,0.5, 0.0};

        renderer.render();

        display.update();
    }

    return 0;
}
