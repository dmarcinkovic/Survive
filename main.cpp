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

    Entity2D entity1(texture, glm::vec3{-0.5, 0.5, 0.0}, 0.3);
    Entity2D entity2(texture, glm::vec3{0.5, 0.5, 0.0}, 0.3);
    Entity2D entity3(texture1, glm::vec3{-0.5, -0.5, 0.0}, 0.3);

    renderer.addEntity(entity1);
    renderer.addEntity(entity2);
    renderer.addEntity(entity3);

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
