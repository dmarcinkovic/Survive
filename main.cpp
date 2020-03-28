
#include "engine/display/Display.h"
#include "engine/renderer/Loader.h"
#include "engine/shader/Shader.h"
#include "engine/texture/Texture.h"
#include "engine/gui/GuiRenderer.h"
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

    renderer.addEntity(Entity2D(texture, glm::vec3{-0.5, 0.5, 0.0}, 0.3));
    renderer.addEntity(Entity2D(texture, glm::vec3{0.5, 0.5, 0.0}, 0.3));
    renderer.addEntity(Entity2D(texture1, glm::vec3{0.5, -0.5, 0.0}, 0.3));

    while (display.isRunning())
    {
        Display::clearWindow();

        renderer.render();

        display.update();
    }

    return 0;
}
