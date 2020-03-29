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

    Texture texture(renderer.getModel(),loader.loadTexture("res/apple.png"));
    Texture texture1(renderer.getModel(),loader.loadTexture("res/texture.jpg"));
    Texture texture2(renderer.getModel(), loader.loadTexture("res/walking.png"));

    renderer.addGui(Entity2D(texture, glm::vec3{-0.5, 0.5, 0.0}, 0.3));
    renderer.addGui(Entity2D(texture, glm::vec3{0.5, 0.5, 0.0}, 0.3));
    renderer.addGui(Entity2D(texture1, glm::vec3{0.5, -0.5, 0.0}, 0.3));
    renderer.addSprite(Entity2D(texture2, glm::vec3{-0.5, -0.5, 0.0}, 0.3));

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
